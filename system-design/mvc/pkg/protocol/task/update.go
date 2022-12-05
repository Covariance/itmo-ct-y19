package task

import (
	"gotodo/pkg/model"
)

type UpdateRequest struct {
	Id uint64           `json:"id"`
	To model.TaskStatus `json:"to"`
}

type UpdateResponse struct{}
