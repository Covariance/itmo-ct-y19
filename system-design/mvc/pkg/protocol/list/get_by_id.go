package list

import (
	"gotodo/pkg/model"
)

type GetByIdRequest struct {
	Id uint64 `json:"id"`
}

type GetByIdResponse struct {
	TaskList model.TaskList `json:"task_list"`
}
