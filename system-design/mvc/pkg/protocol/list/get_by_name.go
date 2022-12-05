package list

import (
	"gotodo/pkg/model"
)

type GetByNameRequest struct {
	Name string `json:"name"`
}

type GetByNameResponse struct {
	TaskLists []model.TaskList `json:"task_lists"`
}
