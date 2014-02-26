#include "JSBKBLib.h"
#include "jsapi.h"
#include "cocos2d.h"
#include "cocos2d_specifics.hpp"

// Binding specific object
JSClass*        jsb_mask_class;
JSObject*       jsb_mask_prototype;

JSBool js_constructor(JSContext* cx, uint32_t argc, jsval* vp){
    cocos2d::CCLog("Mask: JS Constructor...");
    if (argc == 0) {
        Mask* cobj = new Mask();
        cocos2d::CCObject* ccobj = dynamic_cast<cocos2d::CCObject*>(cobj);
        
        if (ccobj) {
            ccobj->autorelease();
        }
        TypeTest<Mask> t;
        js_type_class_t* typeClass;
        uint32_t typeId = t.s_id();
        HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
        assert(typeClass);
        JSObject* obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
        
        js_proxy_t* p = jsb_new_proxy(cobj, obj);
        JS_AddNamedObjectRoot(cx, &p->obj, "Mask");
        
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "Mask: Wrong number of arguments: %d, was expecting: %d", argc, 0);
    
    return JS_FALSE;
}

JSBool js_initWithObject(JSContext* cx, uint32_t argc, jsval* vp){
    cocos2d::CCLog("Mask: js is initing with...");

    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;

    do {
        if (argc == 2) {
            cocos2d::CCNode* arg0;
            do {
                if (!argv[0].isObject()) {
                    ok = JS_FALSE; break;
                }
                js_proxy_t *proxy0;
                JSObject *tmpObj0 = JSVAL_TO_OBJECT(argv[0]);
                proxy0 = jsb_get_js_proxy(tmpObj0);
                if (proxy0) {
                    arg0 = (cocos2d::CCNode*)(proxy0->ptr);
                }
                else {
                    arg0 = NULL;
                }
                int i = 100 + 2;
                i++;
                // arg0 = (cocos2d::CCNode*)(proxy0 ? proxy0->ptr : NULL);
                JSB_PRECONDITION2(arg0, cx, JS_FALSE, "Mask: Invalid Native Object");
            } while (0);
            if (!ok) { ok = JS_TRUE; break; }

            cocos2d::CCSprite* arg1;
            do {
                if (!argv[1].isObject()) { ok = JS_FALSE; break; }
                js_proxy_t *proxy1;
                JSObject *tmpObj1 = JSVAL_TO_OBJECT(argv[1]);
                proxy1 = jsb_get_js_proxy(tmpObj1);
                arg1 = (cocos2d::CCSprite*)(proxy1 ? proxy1->ptr : NULL);
                JSB_PRECONDITION2(arg1, cx, JS_FALSE, "Mask: Invalid Native Object");
            } while (0);
            if (!ok) { ok = JS_TRUE; break; }

            JSObject* thisObj = JS_THIS_OBJECT(cx, vp);
            if (thisObj) {
                js_proxy_t* proxy = jsb_get_js_proxy(thisObj);
                
                if (proxy) {
                    ((Mask* )proxy->ptr)->initWithObject(arg0, arg1);
                    CCLog("initWithObject succeed!");
                    return JS_TRUE;
                }
            }

            return JS_FALSE;
        }
    } while (0);

    JS_ReportError(cx, "Mask: Wrong number of arguments: %d, was expecting: %d", argc, 2);
    
    return JS_FALSE;
}

JSBool js_mask(JSContext* cx, uint32_t argc, jsval* vp){
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;

    do {
        if (argc == 0) {
            JSObject* thisObj = JS_THIS_OBJECT(cx, vp);
            if (thisObj) {
                js_proxy_t* proxy = jsb_get_js_proxy(thisObj);
                
                if (proxy) {
                    ((Mask* )proxy->ptr)->mask();
                    return JS_TRUE;
                }
            }

            return JS_FALSE;
        }
    } while (0);

    JS_ReportError(cx, "Mask: Wrong number of arguments: %d, was expecting: %d", argc, 0);
    
    return JS_FALSE;
}

JSBool js_maskWithClear(JSContext* cx, uint32_t argc, jsval* vp){
    cocos2d::CCLog("Mask: js is masking with clear...");

    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;

    do {
        if (argc == 4) {
            double arg0;
            ok &= JS_ValueToNumber(cx, argv[0], &arg0);
            double arg1;
            ok &= JS_ValueToNumber(cx, argv[1], &arg1);
            double arg2;
            ok &= JS_ValueToNumber(cx, argv[2], &arg2);
            double arg3;
            ok &= JS_ValueToNumber(cx, argv[3], &arg3);
            if (!ok) { ok = JS_TRUE; break; }

            JSObject* thisObj = JS_THIS_OBJECT(cx, vp);
            if (thisObj) {
                js_proxy_t* proxy = jsb_get_js_proxy(thisObj);
                
                if (proxy) {
                    ((Mask* )proxy->ptr)->maskWithClear(arg0, arg1, arg2, arg3);
                    CCLog("mask with clear succeed!");
                    return JS_TRUE;
                }
            }

            return JS_FALSE;
        }
    } while (0);

    JS_ReportError(cx, "Mask: Wrong number of arguments: %d, was expecting: %d", argc, 4);
    
    return JS_FALSE;
}

JSBool js_reDrawMask(JSContext* cx, uint32_t argc, jsval* vp){
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;

    do {
        if (argc == 0) {
            JSObject* thisObj = JS_THIS_OBJECT(cx, vp);
            if (thisObj) {
                js_proxy_t* proxy = jsb_get_js_proxy(thisObj);
                
                if (proxy) {
                    ((Mask* )proxy->ptr)->reDrawMask();
                    return JS_TRUE;
                }
            }

            return JS_FALSE;
        }
    } while (0);

    JS_ReportError(cx, "Mask: Wrong number of arguments: %d, was expecting: %d", argc, 0);
    
    return JS_FALSE;
}

extern JSObject *jsb_CCNode_prototype;

void js_finalize(JSFreeOp* fop, JSObject* obj){
    CCLOGINFO("Mask: finallizing JS object %p Mask", obj);
}

void js_register_mask(JSContext* cx, JSObject* global){
    jsb_mask_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mask_class->name = "Mask";
    jsb_mask_class->addProperty = JS_PropertyStub;
    jsb_mask_class->delProperty = JS_PropertyStub;
    jsb_mask_class->getProperty = JS_PropertyStub;
    jsb_mask_class->setProperty = JS_StrictPropertyStub;
    jsb_mask_class->enumerate = JS_EnumerateStub;
    jsb_mask_class->resolve = JS_ResolveStub;
    jsb_mask_class->convert = JS_ConvertStub;
    jsb_mask_class->finalize = js_finalize;
    jsb_mask_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSFunctionSpec funcs[] = {
        JS_FN("initWithObject", js_initWithObject, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("mask", js_mask, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("maskWithClear", js_maskWithClear, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("reDrawMask", js_reDrawMask, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSPropertySpec properties[] = {
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };
    
    // Binding create() function and prototype
    jsb_mask_prototype = JS_InitClass(
                                 cx, global,
                                 jsb_CCNode_prototype,
                                 jsb_mask_class,
                                 js_constructor, 0,
                                 properties,
                                 funcs,
                                 NULL,
                                 NULL);
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "Mask", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
    
    TypeTest<Mask> t;
    js_type_class_t* p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    
    if (!p) {
        p = (js_type_class_t* )malloc(sizeof(_js_global_type_ht));
        p->type = typeId;
        p->jsclass = jsb_mask_class;
        p->proto = jsb_mask_prototype;
        p->parentProto = jsb_CCNode_prototype;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}

void register_mask_all(JSContext* cx, JSObject* obj){
    jsval nsval;
    JSObject* ns;
    JS_GetProperty(cx, obj, "kb", &nsval);
    
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "kb", &nsval);
    }
    else{
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;
    js_register_mask(cx, obj);
}
