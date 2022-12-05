package model

import (
	"math/rand"
)

type Task struct {
	Id          uint64
	Name        string
	Status      TaskStatus
	Description string
}

func NewTask(name, description string) Task {
	return Task{
		Id:          rand.Uint64(),
		Name:        name,
		Status:      BACKLOG,
		Description: description,
	}
}

func (r *DBConn) AddTask(task Task) error {
	// TODO
	return nil
}

func (r *DBConn) GetTaskById(id uint64) (Task, error) {
	// TODO
	return Task{}, nil
}

func (r *DBConn) GetTasksByName(name string) ([]Task, error) {
	// TODO
	return []Task{}, nil
}

func (r *DBConn) ChangeTaskStatus(id uint64, status TaskStatus) error {
	// TODO
	return nil
}

func (r *DBConn) DeleteTask(id uint64) error {
	// TODO
	return nil
}
