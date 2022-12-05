package main

import (
	"gotodo/pkg/controller"
	"gotodo/pkg/model"
	"log"

	"github.com/gin-gonic/gin"
)

func main() {
	lg := log.Default()

	db, err := model.NewDBConn()
	if err != nil {
		lg.Fatalf("Unable to get DB connection: %v", err)
	}

	connectivity := controller.Connectivity{DBConn: &db}

	router := gin.Default()

	router.POST("/list/create", connectivity.CreateList)
	router.POST("/list/get/id", connectivity.GetListById)
	router.POST("/list/get/name", connectivity.GetListsByName)

	router.POST("/task/create", connectivity.CreateTask)
	router.POST("/task/get/id", connectivity.GetTaskById)
	router.POST("/task/get/name", connectivity.GetTasksByName)
	router.POST("/task/update", connectivity.UpdateTask)
	router.POST("/task/addToList", connectivity.AddTaskToList)

	lg.Println("GoToDo server started")
}
