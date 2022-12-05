package task

type AddToListRequest struct {
	ListId uint64 `json:"listId"`
	TaskId uint64 `json:"taskId"`
}

type AddToListResponse struct{}
