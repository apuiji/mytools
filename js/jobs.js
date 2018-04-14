(function(pack){
pack.parallel = function(jobs){
	var each, init, done;
	return {
		run:function(){
			var ctx = {
				_this:this, _arguments:[].slice.call(arguments)
			};
			'function'==typeof(init) && init(ctx);
			var count = jobs.length;
			for(var i=0;i<jobs.length;++i){
				if('function'==typeof(each))each(jobs[i],ctx,ok);
				else if('function'==typeof(jobs[i]))jobs[i](ctx,ok);
				else ok();
			}
			function ok(){if(--count<=0)done(ctx); }
		},
		each:function(fn){ return each = fn, this; },
		init:function(fn){ return init = fn, this; },
		done:function(fn){ return done = fn, this; },
	}
};
pack.serial = function(jobs){
	var each, init;
	return {
		run:function(){
			var ctx = {
				_this:this, _arguments:[].slice.call(arguments)
			};
			'function' == typeof(init) && init(ctx);
			var i = 0;
			ok();
			function ok(){
				if('function'==typeof(each))each(jobs[i],ctx,ok);
				else if('function'==typeof(jobs[i]))jobs[i](ctx,ok);
				else ok();
				++i;
			}
		},
		each:function(fn){ return each = fn, this; },
		init:function(fn){ return init = fn, this; },
	}
};
})(this);
