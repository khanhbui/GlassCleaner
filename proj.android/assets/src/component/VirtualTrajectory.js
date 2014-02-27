var VirtualTrajectory = Trajectory.extend({
	: function( $super, length, colorHead, colorTail, colorNinjaStar ) {
		$super( null, length, colorHead, colorTail, colorNinjaStar );
		
		this.virtualInput = {
			isActivated: true,
			tasks      : [],
			nextTask   : null
		};
		this.defineVirtualTouchObj();
		
		this.luxuriousMode = true; // より強力そうなエフェクトにしたいならこれを true に
	},
	
	//--------------------------------------------------------------------------
	defineVirtualTouchObj: function() {
		this.virtualTouchObj = {
			scale: Core.Capabilities.getScreenWidth() / 320,
			x: 0,
			y: 0,
			nextX: 0,
			nextY: 0,
			vecX : 0,
			vecY : 0,
			vecDelay: 0.2,
			action: null,
			event : null,
			span  : 0,
			
			setPosition: function( x, y ) {
				this.x = x * this.scale;
				this.y = y * this.scale;
			},
			setNextPosition: function( x, y ) {
				this.nextX = x * this.scale;
				this.nextY = y * this.scale;
			},
			approachNextPosition: function() {
				this.span -= dn.Timekeeper.getPassedSec();
				if (this.span < 0.1) { this.span = 0.1; }
				var targetVecX = dn.Timekeeper.getDelta( (this.nextX - this.x), this.span );
				var targetVecY = dn.Timekeeper.getDelta( (this.nextY - this.y), this.span );
				this.vecX += nj.battle.Util.toward( this.vecX, targetVecX, this.vecDelay );
				this.vecY += nj.battle.Util.toward( this.vecY, targetVecY, this.vecDelay );
				this.x += this.vecX;
				this.y += this.vecY;
			},
			getPosition: function() {
				return new Core.Point( this.x, this.y );
			},
			getOriginalPosition: function() {
				return new Core.Point( this.x / this.scale, this.y / this.scale );
			},
			getAction: function() {
				switch (this.event) {
				case 'start': return this.Action.Start;
				case 'end'  : return this.Action.End;
				case 'move' : return this.Action.Move;
				default     : return undefined;
				}
			},
			getId: function() {
				return 1;
			},
			Action: {
				Start: 0,
				End  : 1,
				Move : 2
			}
		};
	},
	
	//--------------------------------------------------------------------------
	onUpdate: function( $super, delta ) {
		$super( delta );
		
		//----- 助太刀の剣閃は仮想入力で実現する
		if (this.virtualInput.isActivated) {
			this.playVirtualInput();
		}
	},
	
	//--------------------------------------------------------------------------
	setVirtualInputDummyData: function() {
		var data = [
			[0.3, 300, 100, 'start_end'],
			[0.6, 200, 150, 'start_end'],
			[0.3, 100, 200, 'start_end'],
			[0.4, 100,  50, 'start'],
			[0.4, 300, 270, 'move'],
			[0.4, 240, 100, 'move'],
			[0.4,  30, 250, 'move'],
			[0.7, 400, 100, 'end']
		];
		
		dn.each( data, function(i) {
			this.pushVirtualInput( i[0], i[1], i[2], i[3] );
		}.bind( this ));
	},
	
	// @param {String} actionType 'start' or 'end' or 'start_end'
	//--------------------------------------------------------------------------
	pushVirtualInput: function( waitSec, x, y, action ) {
		this.virtualInput.tasks.push({
			waitSec: waitSec,
			x      : x,
			y      : y,
			action : action
		});
	},
	
	//--------------------------------------------------------------------------
	playVirtualInput: function() {
		var vi  = this.virtualInput;
		var vto = this.virtualTouchObj;
		
		//----- ongoing virtual touch event handling
		if (vto.action === 'move') {
			vto.event = 'move';
			vto.approachNextPosition();
			this.onTouch( vto );
			
			if (this.luxuriousMode) { //剣閃に水色の粒子が散るエフェクト
				if (dn.rand(100) < 75) {
					nj.EffectFactory.particle(
						vto.getOriginalPosition().getX(),
						vto.getOriginalPosition().getY(),
						-vto.vecX,
						-vto.vecY,
						1.0
					);
				}
			}
		}
		
		//----- set next touch event
		if (! vi.nextTask) {
			if (! vi.tasks.length) { return; }
			vi.nextTask = vi.tasks.shift();
			var t = vi.nextTask;
			
			var sendTouchEvent = function() {
				vto.setPosition( t.x, t.y );
				
				switch (t.action) {
				case 'start_end': //----- throw ninjastar
					vto.event = 'start';
					this.onTouch( vto );
					vto.event = 'end';
					this.onTouch( vto );
					vto.action = null;
					
					if (this.luxuriousMode) { // 手裏剣で水色の粒子が飛ぶエフェクト
						nj.EffectFactory.particleRadial(
							3,
							vto.getOriginalPosition().getX(),
							vto.getOriginalPosition().getY(),
							10,
							0.6
						);
					}
					break;
					
				case 'start': //----- move blade trajectory
				case 'move':
					vto.event = t.action;
					vto.action = 'move';
					this.onTouch( vto );
					if (vi.tasks.length) {
						var nt = vi.tasks[0];
						vto.setNextPosition( nt.x, nt.y );
						vto.span = nt.waitSec;
					} else {
						vto.span = 0;
					}
					break;
					
				case 'end': //----- end blade trajectory
					vto.event = 'end';
					this.onTouch( vto );
					vto.action = null;
					break;
				}
				vi.nextTask = null;
			}.bind( this );
			
			setTimeout( sendTouchEvent, t.waitSec );
		}
	}
});

