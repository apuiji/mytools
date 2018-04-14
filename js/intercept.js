(function(pack){
pack.before = function(fn,before){
	var II = function(){
		var ctx = { _this:this, _arguments:[].slice.call(arguments) };
		before(ctx);
		if(ctx._stop)return ctx._stop;
		return fn.apply(ctx._this, ctx._arguments);
	}
	return II.__proto__ = fn, II;
};
pack.after = function(fn,after){
	var II = function(){
		var ctx = { _this:this, _arguments:[].slice.call(arguments), _return:fn.apply(this,arguments) };
		return after(ctx) || ctx._return;
	}
	return II.__proto__ = fn, II;
};
})(this);
