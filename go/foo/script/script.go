package main

import (
    "os"
    "os/exec"
)


func main() {
    // Replace `ls` (and its arguments) with something more interesting
    cmd := exec.Command("python", "script.py")
    cmd.Stdout = os.Stdout
    cmd.Stderr = os.Stderr
    cmd.Run()
}

