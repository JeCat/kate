
// kate shell 加载完成事件
function onKateLoaded()
{
	// 按钮事件
	$("#btnOpenConsole").click(function(){
		alert(kateapi.wndId) ;
		kateapi.inspector(kateapi.wndId) ;
		//kate.window.inspector() ;
	}) ;


}

function getValue()
{
	return $("[name=num]").val() ;
}