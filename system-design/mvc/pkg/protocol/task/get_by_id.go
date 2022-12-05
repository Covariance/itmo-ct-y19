package task

import (
	"gotodo/pkg/model"
)

type GetByIdRequest struct {
	Id uint64 `json:"id"`
}

type GetByIdResponse struct {
	Task model.Task `json:"task"`
}
