#include "JSBKBLib.h"
#include "cocos2d_specifics.hpp"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::RootedValue initializing(cx);
    JSBool isNewValid = JS_TRUE;
    JSObject* global = ScriptingCore::getInstance()->getGlobalObject();
	isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && JSVAL_TO_BOOLEAN(initializing);
	if (isNewValid)
	{
		TypeTest<T> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
        
		JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
		return JS_TRUE;
	}
    
    JS_ReportError(cx, "Don't use `new cc.XXX`, please use `cc.XXX.create` instead! ");
    return JS_FALSE;
}

static JSBool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
	vp.set(BOOLEAN_TO_JSVAL(JS_TRUE));
	return JS_TRUE;
}

// Binding specific object
JSClass*        jsb_mask_class;
JSObject*       jsb_mask_prototype;

JSBool js_mask_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	
	do {
		if (argc == 2) {
            cocos2d::Sprite* arg0;
			do {
				if (!argv[0].isObject()) { ok = JS_FALSE; break; }
				js_proxy_t *proxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
				proxy = jsb_get_js_proxy(tmpObj);
				arg0 = (cocos2d::Sprite*)(proxy ? proxy->ptr : NULL);
				JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = JS_TRUE; break; }
            
            cocos2d::Sprite* arg1;
			do {
				if (!argv[0].isObject()) { ok = JS_FALSE; break; }
				js_proxy_t *proxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
				proxy = jsb_get_js_proxy(tmpObj);
				arg1 = (cocos2d::Sprite*)(proxy ? proxy->ptr : NULL);
				JSB_PRECONDITION2( arg1, cx, JS_FALSE, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = JS_TRUE; break; }
            
			Mask* ret = Mask::create(arg0, arg1);
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *proxy = js_get_or_create_proxy<Mask>(cx, (Mask*)ret);
					jsret = OBJECT_TO_JSVAL(proxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while (0);
	JS_ReportError(cx, "js_Mask_create : wrong number of arguments");
	return JS_FALSE;
}

extern JSObject *jsb_cocos2d_Node_prototype;

void js_mask_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Mask)", obj);
}

static JSBool js_mask_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    Mask *nobj = Mask::create();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "Mask");
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

JSBool js_maskWithClear(JSContext* cx, uint32_t argc, jsval* vp){
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
                    return JS_TRUE;
                }
            }

            return JS_FALSE;
        }
    } while (0);

    JS_ReportError(cx, "Mask: Wrong number of arguments: %d, was expecting: %d", argc, 4);
    
    return JS_FALSE;
}

void js_register_mask(JSContext* cx, JSObject* global){
    jsb_mask_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mask_class->name = "Mask";
    jsb_mask_class->addProperty = JS_PropertyStub;
    jsb_mask_class->delProperty = JS_DeletePropertyStub;
    jsb_mask_class->getProperty = JS_PropertyStub;
    jsb_mask_class->setProperty = JS_StrictPropertyStub;
    jsb_mask_class->enumerate = JS_EnumerateStub;
    jsb_mask_class->resolve = JS_ResolveStub;
    jsb_mask_class->convert = JS_ConvertStub;
    jsb_mask_class->finalize = js_mask_finalize;
    jsb_mask_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSFunctionSpec funcs[] = {
        JS_FN("maskWithClear", js_maskWithClear, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_mask_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};
    
    static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_mask_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};
    
    // Binding create() function and prototype
    jsb_mask_prototype = JS_InitClass(
                                 cx, global,
                                 jsb_cocos2d_Node_prototype,
                                 jsb_mask_class,
                                 dummy_constructor<Mask>, 0,
                                 properties,
                                 funcs,
                                 NULL,
                                 st_funcs);
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "Mask", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
    
    TypeTest<Mask> t;
    js_type_class_t *p;
	std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_mask_class;
		p->proto = jsb_mask_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_mask_all(JSContext* cx, JSObject* obj){
    JS::RootedValue nsval(cx);
	JSObject *ns;
	JS_GetProperty(cx, obj, "kb", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "kb", nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;
    
    js_register_mask(cx, obj);
}
