package model

type TaskStatus int

const (
	BACKLOG TaskStatus = iota
	UP_NEXT
	FROZEN
	IN_PROGRESS
	AWAITING_FEEDBACK
	FINISHED
)
