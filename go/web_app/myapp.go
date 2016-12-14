package main

import (
        "fmt"
        "github.com/gorilla/mux"
        "net/http"
       )

var router = mux.NewRouter()

const indexPage = `
    <h1>Login</h1>
    <form method="post" action="/login">
    <label for="name">User name</label>
    <input type="text" id="name" name="name">
    <label for="password">Password</label>
    <input type="password" id="password" name="password">
    <button type="submit">Login</button>
    </form>
`

func indexPageHandler(response http.ResponseWriter, request *http.Request) {
   fmt.Fprintf(response, indexPage)
}

func internalPageHandler(response http.ResponseWriter, request *http.Request) {
    fmt.Fprintf(response, indexPage)
}

func main() {
   fmt.Println("Server is ... UP")

   router.HandleFunc("/", indexPageHandler)
   router.HandleFunc("/internal", internalPageHandler)

   http.Handle("/", router)
   http.ListenAndServe(":8080", nil)
}
