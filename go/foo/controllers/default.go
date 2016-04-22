package controllers

import (
	"github.com/astaxie/beego"
)

type MainController struct {
	beego.Controller
}

func (c *MainController) Get() {
	c.TplNames = "foo.html"
}

func (c *MainController) Foo() {
	c.TplNames = "foo.html"
}

