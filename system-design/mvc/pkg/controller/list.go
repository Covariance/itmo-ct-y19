package controller

import (
	"gotodo/pkg/model"
	protocol "gotodo/pkg/protocol/list"
	"net/http"

	"github.com/gin-gonic/gin"
)

func (r *Connectivity) CreateList(context *gin.Context) {
	var request protocol.CreateRequest
	if err := context.ShouldBindJSON(&request); err != nil {
		context.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	list := model.NewTaskList(request.Name)

	if err := r.DBConn.AddTaskList(list); err != nil {
		context.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
	}

	response := protocol.CreateResponse{
		Id: list.Id,
	}

	context.JSON(http.StatusCreated, response)
}

func (r *Connectivity) GetListById(context *gin.Context) {
	var request protocol.GetByIdRequest
	if err := context.ShouldBindJSON(&request); err != nil {
		context.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	list, err := r.DBConn.GetTaskListById(request.Id)
	if err != nil {
		context.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
	}

	response := protocol.GetByIdResponse{
		TaskList: list,
	}

	context.JSON(http.StatusOK, response)
}

func (r *Connectivity) GetListsByName(context *gin.Context) {
	var request protocol.GetByNameRequest
	if err := context.ShouldBindJSON(&request); err != nil {
		context.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	lists, err := r.DBConn.GetTaskListsByName(request.Name)
	if err != nil {
		context.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
	}

	response := protocol.GetByNameResponse{
		TaskLists: lists,
	}

	context.JSON(http.StatusOK, response)
}
