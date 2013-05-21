// kate shell 加载完成事件
function onKateLoaded()
{
	// 显示窗口 (默认是不显示窗口的)
	kate.window.show() ;

	var secondWindow ;

	// 按钮事件
	$("#btnOpenConsole").click(function(){
		kate.window.inspector() ;
	}) ;

	$("#btnOpenWindow").click(function(){
		secondWindow = kate.createWindow(kate.appFolder+'/dialog.html') ;
		secondWindow.show() ;
	}) ;

	$("#btnRead").click(function(){
		if( !secondWindow )
		{
			alert("窗口还没有打开") ;
			return ;
		}

		alert( secondWindow.call("getValue") ) ;
	}) ;
}