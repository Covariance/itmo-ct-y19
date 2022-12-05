package task

import (
	"gotodo/pkg/model"
)

type GetByNameRequest struct {
	Name string `json:"name"`
}

type GetByNameResponse struct {
	Tasks []model.Task `json:"tasks"`
}
