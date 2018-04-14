(function(pack,name){
pack[name] = function(js,cfg){
	var ctx = new Context(js,cfg);
	do{
		matchers[ctx.state[ctx.state.length-1]](ctx);
	}while(!ctx.isend());
	ctx.result.push(ctx.js.substr(ctx.mark));
	return ctx;
};
var matchers = {
	common:function(thiz){
		var m = thiz.match(/\/\/|\/\*|[\/'"`\{\}]/g);
		var state, push = true;
		if(m)switch(m[0]){
		case'//':state = state||'line';
		case'/*':state = state||'block';
			state += '_comment';
			break;
		case'/':
			if(isRegExp(thiz,m))state = 'slash';
			else{ push=false; break; }
		case"'":state = state||'single';
		case'"':state = state||'double';
		case'`':state = state||'reverse';
			state += '_quot_string';
			break;
		case'}':
			if(thiz.layer==thiz.layermark[thiz.layermark.length-1]){
				thiz.layermark.pop();	thiz.state.pop();
				break;
			}
			thiz.layer -= 2;
		case'{':
			++thiz.layer;	push=false;
		}else{
			thiz.end = true;
			return;
		}
		thiz.appReplacement(m, push);
		if(state)thiz.state.push(state);
	},
	line_comment :function(thiz){comment(thiz,/\n|$/g)},
	block_comment:function(thiz){comment(thiz,/\*\//g)},
	single_quot_string: function(thiz){string(thiz,"'")},
	double_quot_string: function(thiz){string(thiz,'"')},
	reverse_quot_string:function(thiz){string(thiz,'(`|\\$\\{)')},
	slash_quot_string:  function(thiz){string(thiz,'\\/[gimyu]*')}
};
function Context(js,cfg){
	cfg = cfg||{};
	this.js = js;
	if(cfg.keepcomment)this.keepcomment = cfg.keepcomment;
	this.i = this.mark = cfg.start||0;
	this.layer = cfg.layer||1;	this.layermark = [this.layer];
	this.until = cfg.until||js.length;
	this.result = [''];	this.state = ['common'];
}
Context.prototype = {
	isend:function(){
		if(this.end)return true;
		if('function'==typeof(this.until))return this.until();
		return this.i>=this.until*1;
	},match:function(re){
		re.lastIndex = this.i;
		return re.exec(this.js);
	},appReplacement:function(m,push){
		var cont = this.js.substring(this.mark,m.index);
		this.result[this.result.length-1] += cont;
		if(push)this.result.push(m[0]);
		else this.result[this.result.length-1]+=m[0];
		this.mark = this.i = m.index+m[0].length;
	},join:function(){
		var result = new Array(this.result.length);
		var layer = 1, layermark = [1];
		for(var i=0;i<result.length;++i){
			result[i] = this.result[i];
			if(result[i] instanceof SrcPart)continue;
			var m = /^(?:\/\/|\/\*|[\/'"`\}])/.exec(result[i]);
			if(m)switch(m[0]){
			case'/':
				if(isRegExp(this,null,i))continue;
				else break;
			case'}':
				if(layer!=layermark[layermark.length-1])break;
				layermark.pop();
			case'`':
				if(result[i][result[i].length-1]=='{')layermark.push(layer);
			default:
				continue;
			}
			result[i] = result[i].replace(/\r\n|[\{\}\n;]/g, function(g){
				var s = '', e = '';
				switch(g[0]){
				case'{':++layer;
				case';':s=g[0];break;
				case'}':e=g[0];--layer;
				}
				return s+'\n'+new Array(layer).join('\t')+e;
			});
		}
		return result.join('');
	}
};
function isRegExp(thiz,m,i){
	i = i==null?thiz.result.length-1:i;
	var last = m && thiz.js.substring(thiz.mark,m.index);
	for(;true;last=thiz.result[i--]){
		if('string'==typeof(last)){
			if(last.trim())return /(\b(case|else|return|yield)\b|[^\w\)\]])\s*$/.test(last);
		}else if(last instanceof SrcPart){
			if(last.type!='comment')return false;
		}else if(i<0)return true;
	}
}
function comment(thiz,end){
	var m = thiz.match(end);
	thiz.appReplacement(m);
	if(thiz.keepcomment)thiz.result[thiz.result.length-1] = new SrcPart(thiz.result[thiz.result.length-1],'comment');
	else thiz.result.pop();
	thiz.state.pop();
	thiz.result.push('');
}
function string(thiz,quot){
	var m = thiz.match(new RegExp('(?:(?:\\\\)?(?:\\n|.))*?'+quot, 'g'));
	thiz.appReplacement(m);
	if(m[2]=='${'){
		thiz.state.push('common');
		thiz.layermark.push(thiz.layer);
	}else thiz.state.pop();
	thiz.result[thiz.result.length-1] = new SrcPart(thiz.result[thiz.result.length-1],'string');
	thiz.result.push('');
}
function SrcPart(src,type){
	return this.src = src, this.type = type, this;
}
SrcPart.prototype = {
	toString:function(){return this.src}
}
})(xx.match,'ecma6decompressor');