package controller

import (
	"gotodo/pkg/model"
	protocol "gotodo/pkg/protocol/task"
	"net/http"

	"github.com/gin-gonic/gin"
)

func (r *Connectivity) CreateTask(context *gin.Context) {
	var request protocol.CreateRequest
	if err := context.ShouldBindJSON(&request); err != nil {
		context.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	task := model.NewTask(request.Name, request.Description)

	if err := r.DBConn.AddTask(task); err != nil {
		context.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
	}

	response := protocol.CreateResponse{
		Id: task.Id,
	}

	context.JSON(http.StatusCreated, response)
}

func (r *Connectivity) AddTaskToList(context *gin.Context) {
	var request protocol.AddToListRequest
	if err := context.ShouldBindJSON(&request); err != nil {
		context.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	if err := r.DBConn.AddTaskToListById(request.ListId, request.TaskId); err != nil {
		context.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
	}

	response := protocol.AddToListResponse{}

	context.JSON(http.StatusOK, response)
}

func (r *Connectivity) UpdateTask(context *gin.Context) {
	var request protocol.UpdateRequest
	if err := context.ShouldBindJSON(&request); err != nil {
		context.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	if err := r.DBConn.ChangeTaskStatus(request.Id, request.To); err != nil {
		context.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
	}

	response := protocol.CreateResponse{}

	context.JSON(http.StatusOK, response)
}

func (r *Connectivity) GetTaskById(context *gin.Context) {
	var request protocol.GetByIdRequest
	if err := context.ShouldBindJSON(&request); err != nil {
		context.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	task, err := r.DBConn.GetTaskById(request.Id)
	if err != nil {
		context.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
	}

	response := protocol.GetByIdResponse{
		Task: task,
	}

	context.JSON(http.StatusOK, response)
}

func (r *Connectivity) GetTasksByName(context *gin.Context) {
	var request protocol.GetByNameRequest
	if err := context.ShouldBindJSON(&request); err != nil {
		context.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	tasks, err := r.DBConn.GetTasksByName(request.Name)
	if err != nil {
		context.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
	}

	response := protocol.GetByNameResponse{
		Tasks: tasks,
	}

	context.JSON(http.StatusOK, response)
}
