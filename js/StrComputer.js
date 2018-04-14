(function(pack,name){
pack[name] = function(dom){
	dom = dom||document;
	var span = dom.body.appendChild(dom.createElement('span'));
	span.style.fontSize = '12px';	span.style.display = 'none';
	return {
		dispose:function(){
			dom.body.removeChild(span);
		},box:function(str){
			return span.innerHTML = str, { width:span.offsetWidth/12, height:span.offsetHeight/12 };
		}
	};
};
})(this,'StrComputer');
