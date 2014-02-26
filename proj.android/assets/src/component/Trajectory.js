var Trajectory = cc.Node.extend({
	ctor: function(length, colorHead, colorTail, colorNinjaStar) {
		this._super();

		this.maxLength = length || 30;
		this.colorHead = colorHead || [1, 1, 0];
		this.colorTail = colorTail || [1, 0, 0];
		this.colorNinjaStar = colorNinjaStar;

		this.vertexList = [];
		this.moveCount  = 0;
		this.moveFrame  = 0;
		this.isMoving   = false;
		this.isTouching = false;
		this.isNotEnd   = false;
		this.directionAngle = 0;

		var glass = cc.Sprite.create("res/glass.png");
		glass.setAnchorPoint(cc.p(0, 0));
		this.addChild(glass);

		var bg1 = cc.Sprite.create("res/bg1.png");
		bg1.setAnchorPoint(cc.p(0, 0));
		this.sun = cc.Sprite.create("res/sun.png");
		this.sun.setAnchorPoint(cc.p(0, 0));
		this.sun.setPosition(Utils.p(50, 100));
		var bg2 = cc.Sprite.create("res/bg2.png");
		bg2.setAnchorPoint(cc.p(0, 0));
		var objectSprite = cc.Node.create();
		objectSprite.addChild(bg1);
		objectSprite.addChild(this.sun);
		objectSprite.addChild(bg2);

		this.prim = cc.DrawNode.create();

		var maskSprite = cc.Sprite.create("res/mask.png");
		maskSprite.setAnchorPoint(cc.p(0, 0));
		maskSprite.addChild(this.prim);

		this._mask = new kb.Mask();
		this._mask.initWithObject(objectSprite, maskSprite);
        this.addChild(this._mask);

        this.text = cc.LabelBMFont.create("Sun:0", "res/font/font.fnt", 35, cc.TEXT_ALIGNMENT_LEFT);
        this.text.setAnchorPoint(cc.p(0, 0));
        this.text.setPosition(Utils.p(15, 480 - 50));
        this.addChild(this.text);

		this.tapCount = 0;

		this.x = 0;
		this.y = 0;
		this.prevTouchId = null;

		this.bladePower       = 1.0 ;
		this.bladePowerMin    = 0.7 ;
		this.bladeDecrement   = 0.03;
		this.bladeRecoverTime = 1.0;

		this.scaleNumber = 0;
		this.scaleSign = 1;
		this.sunScore = 0;
	},

	getLength: function() {
		return this.vertexList.length;
	},

	isUsingBlade: function() {
		return (this.moveFrame > 15);
	},

	isBladeTooShort: function() {
		return (this.getLength() < 3);
	},

	getDirectionAngle: function() {
		return this.directionAngle;
	},

	update: function(elapsed) {
		var v = this.vertexList;
		var p = this.prim;
		if (v.length >= 2) {
			p.clear();
			p.setVisible(true);

			var bladeWidth = 10 * this.bladePower * 5;
			for (var i=0;  i < v.length - 1;  i++) {
				var grad = 1 - (i / v.length);
				var r = (this.colorHead[0] * grad) + (this.colorTail[0] * (1-grad));
				var g = (this.colorHead[1] * grad) + (this.colorTail[1] * (1-grad));
				var b = (this.colorHead[2] * grad) + (this.colorTail[2] * (1-grad));

				var w  = (i < 4) ? (i * 0.22) : grad;
				var bw = w * bladeWidth;

				var vx  = v[i  ].x;
				var vpx = v[i+1].x;
				var vy  = v[i  ].y;
				var vpy = v[i+1].y;

				if (!v[i].dx) {
					var theta = Math.atan2( vy - vpy, vx - vpx ) * 180 / Math.PI;
					v[i].dx = Math.cos( theta + 90 );
					v[i].dy = Math.sin( theta + 90 );
					this.directionAngle = theta;
				}

				var j = i - 1 < 0 ? 0 : i - 1;
				p.drawSegment(
					cc.p(v[j].x, v[j].y),
					cc.p(v[i].x, v[i].y),
					bw,
					cc.c4(r, g, b, grad)
				);
			}

			var lastVertex = cc.p(v[ v.length - 1 ].x, v[ v.length - 1 ].y);
			for (var i = v.length - 1;  i < this.maxLength;  i++) {
				p.drawSegment(
					lastVertex,
					lastVertex,
					bw,
					cc.c4(r, g, b, 1)
				);
			}

			this._mask.mask();

			this.scaleNumber += 0.04 * this.scaleSign;
			if (Math.abs(this.scaleNumber) > 0.09) {
				this.scaleSign *= -1;
			}
			this.sun.setScale(1 + this.scaleNumber);
		}
		else {
			p.setVisible( false );
		}

		if (!this.isMoving && this.bladePower > 1.0) {
			this.bladePower = 1.0;
		}

		if (v.length > 0 && !this.isMoving) {
			v.pop();
		} else {
			this.isMoving = false;
		}

		if (this.isTouching) {
			this.isTouching = false;
		} else {
			this.tapCount = 0;
		}

		if (this.isNotEnd) {
			++this.moveFrame;
		} else {
			if (this.moveFrame > 0) {
				this.moveFrame /= 3;
				this.moveFrame -= 1;
				if (this.moveFrame < 0) {
					this.moveFrame = 0;
				}
			}
		}
	},

	onTouchBegan: function(touch, event) {
		var scale = 1; //Utils.getScale();
        var x = touch.getLocation().x / scale;
        var y = touch.getLocation().y / scale;

		this.x = x;
		this.y = y;
		this.isMoving   = false;
		this.isTouching = true;

		var vList = this.vertexList;

		this.tapCount++;
		if (this.tapCount > 2) {
			this.tapCount = 2;
		}
		this.isNotEnd = true;

		if (vList.length > this.maxLength) {
			vList.pop();
		}
	},

	onTouchMoved: function(touch, event) {
        var x = touch.getLocation().x;
        var y = touch.getLocation().y;

		this.x = x;
		this.y = y;
		this.isMoving   = false;
		this.isTouching = true;

		var vList = this.vertexList;

		if (this.prevTouchId  &&  this.prevTouchId !== touch.getId()) {
			if (this.tapCount < 2) {
				this.tapCount = 2;
			}
		}
		this.prevTouchId = touch.getId();

		if (this.tapCount > 1) {
			vList = [{x:x, y:y}];
		} else {
			vList.unshift({x:x, y:y});
			this.isMoving = true;
			++this.moveCount;
		}

		if (vList.length === 3) {
			this.countBlade();
		}

		if (vList.length > 10) {
			var diffX = (vList[0].x - vList[1].x) * (vList[1].x - vList[2].x);
			var diffY = (vList[0].y - vList[1].y) * (vList[1].y - vList[2].y);
			if (diffX < 0  ||  diffY < 0) {
				this.countBlade();

				this.bladePower -= this.bladeDecrement;
				if (this.bladePower < this.bladePowerMin) {
					this.bladePower = this.bladePowerMin;
				}
			}
		}

		if (vList.length > this.maxLength) {
			vList.pop();
		}

		this.sunScore++;
		this.text.setString("Sun:" + this.sunScore, true);
	},

	onTouchEnded: function(touch, event) {
		var scale = Utils.getScale();
        var x = touch.getLocation().x / scale;
        var y = touch.getLocation().y / scale;

		this.x = x;
		this.y = y;
		this.isMoving   = false;
		this.isTouching = true;

		var vList = this.vertexList;

		if (this.moveCount < 5) {
			this.countNinjastar();
		}
		this.tapCount--;
		if (this.tapCount < 0) {
			this.tapCount = 0;
		}
		if (this.prevTouchId === touch.getId()) {
			this.prevTouchId = null;
		}
		this.moveCount = 0;
		this.isNotEnd = false;

		if (vList.length > this.maxLength) {
			vList.pop();
		}
	},

	countNinjastar: function() {
	},

	countBlade: function() {
	}
});

