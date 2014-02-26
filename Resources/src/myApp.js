/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

require("src/core/Utils.js");

require("src/component/Trajectory.js");

var MyLayer = cc.Layer.extend({
    ctor:function() {
        this._super();
        cc.associateWithNative(this, cc.Layer);

        this.setKeypadEnabled(true);
        this.setTouchEnabled(true);
    },

    init:function () {
        this._super();

        this._trajectory = new Trajectory();
        this._trajectory.setAnchorPoint(cc.p(0, 0));
        this._trajectory.setPosition(Utils.p(0, 0));
        this.addChild(this._trajectory);

        return true;
    },

    update: function(elapsed) {
        this._trajectory.update(elapsed);
    },

    backClicked: function() {
        cc.Director.getInstance().end();
    },
    
    onTouchesBegan: function(touches, event) {
        this._trajectory.onTouchBegan(touches[0], event);
    },

    onTouchesMoved: function(touches, event) {
        this._trajectory.onTouchMoved(touches[0], event);
    },

    onTouchesEnded: function(touches, event) {
        this._trajectory.onTouchEnded(touches[0], event);
    }
});

var MyScene = cc.Scene.extend({
    ctor:function() {
        this._super();
        this.scheduleUpdate();
        cc.associateWithNative(this, cc.Scene);
    },

    onEnter:function () {
        this._super();
        this._layer = new MyLayer();
        this.addChild(this._layer);
        this._layer.init();
    },

    update: function(elapsed) {
        this._layer.update(elapsed);
    }
});
