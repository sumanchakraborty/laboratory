package routers

import (
	"foo/controllers"
	"github.com/astaxie/beego"
)

func init() {
    beego.Router("/", &controllers.MainController{})
    beego.Router("/foo", &controllers.MainController{}, "post:Foo")
}
