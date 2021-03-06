Type.registerNamespace('BlogServer.WebService');
BlogServer.WebService.AjaxWS=function() {
BlogServer.WebService.AjaxWS.initializeBase(this);
this._timeout = 0;
this._userContext = null;
this._succeeded = null;
this._failed = null;
}
BlogServer.WebService.AjaxWS.prototype={
GetComment:function(id,succeededCallback, failedCallback, userContext) {
return this._invoke(BlogServer.WebService.AjaxWS.get_path(), 'GetComment',false,{id:id},succeededCallback,failedCallback,userContext); },
DelComment:function(id,succeededCallback, failedCallback, userContext) {
return this._invoke(BlogServer.WebService.AjaxWS.get_path(), 'DelComment',false,{id:id},succeededCallback,failedCallback,userContext); },
AddToFavorites:function(entryID,title,url,succeededCallback, failedCallback, userContext) {
return this._invoke(BlogServer.WebService.AjaxWS.get_path(), 'AddToFavorites',false,{entryID:entryID,title:title,url:url},succeededCallback,failedCallback,userContext); }}
BlogServer.WebService.AjaxWS.registerClass('BlogServer.WebService.AjaxWS',Sys.Net.WebServiceProxy);
BlogServer.WebService.AjaxWS._staticInstance = new BlogServer.WebService.AjaxWS();
BlogServer.WebService.AjaxWS.set_path = function(value) { BlogServer.WebService.AjaxWS._staticInstance._path = value; }
BlogServer.WebService.AjaxWS.get_path = function() { return BlogServer.WebService.AjaxWS._staticInstance._path; }
BlogServer.WebService.AjaxWS.set_timeout = function(value) { BlogServer.WebService.AjaxWS._staticInstance._timeout = value; }
BlogServer.WebService.AjaxWS.get_timeout = function() { return BlogServer.WebService.AjaxWS._staticInstance._timeout; }
BlogServer.WebService.AjaxWS.set_defaultUserContext = function(value) { BlogServer.WebService.AjaxWS._staticInstance._userContext = value; }
BlogServer.WebService.AjaxWS.get_defaultUserContext = function() { return BlogServer.WebService.AjaxWS._staticInstance._userContext; }
BlogServer.WebService.AjaxWS.set_defaultSucceededCallback = function(value) { BlogServer.WebService.AjaxWS._staticInstance._succeeded = value; }
BlogServer.WebService.AjaxWS.get_defaultSucceededCallback = function() { return BlogServer.WebService.AjaxWS._staticInstance._succeeded; }
BlogServer.WebService.AjaxWS.set_defaultFailedCallback = function(value) { BlogServer.WebService.AjaxWS._staticInstance._failed = value; }
BlogServer.WebService.AjaxWS.get_defaultFailedCallback = function() { return BlogServer.WebService.AjaxWS._staticInstance._failed; }
BlogServer.WebService.AjaxWS.set_path("/WS/AjaxWS.asmx");
BlogServer.WebService.AjaxWS.GetComment= function(id,onSuccess,onFailed,userContext) {BlogServer.WebService.AjaxWS._staticInstance.GetComment(id,onSuccess,onFailed,userContext); }
BlogServer.WebService.AjaxWS.DelComment= function(id,onSuccess,onFailed,userContext) {BlogServer.WebService.AjaxWS._staticInstance.DelComment(id,onSuccess,onFailed,userContext); }
BlogServer.WebService.AjaxWS.AddToFavorites= function(entryID,title,url,onSuccess,onFailed,userContext) {BlogServer.WebService.AjaxWS._staticInstance.AddToFavorites(entryID,title,url,onSuccess,onFailed,userContext); }
