package task

type CreateRequest struct {
	Name        string `json:"name"`
	Description string `json:"description"`
}

type CreateResponse struct {
	Id uint64 `json:"id"`
}
