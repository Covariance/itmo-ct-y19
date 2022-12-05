package model

import (
	"database/sql"
	"fmt"
	"math/rand"
)

type TaskList struct {
	Id    uint64
	Name  string
	Tasks []uint64
}

func NewTaskList(name string) TaskList {
	return TaskList{
		Id:    rand.Uint64(),
		Name:  name,
		Tasks: []uint64{},
	}
}

func (r *DBConn) AddTaskList(taskList TaskList) error {
	query := `INSERT INTO lists (id, name) VALUES ($1, $2)`
	return r.Conn.QueryRow(query, taskList.Id, taskList.Name).Scan()
}

func (r *DBConn) GetTaskListById(id uint64) (TaskList, error) {
	item := TaskList{}

	query := `SELECT * FROM lists WHERE id = $1;`
	row := r.Conn.QueryRow(query, id)
	switch err := row.Scan(&item.Id, &item.Name, &item.Tasks); err {
	case sql.ErrNoRows:
		return item, fmt.Errorf("no matching record")
	default:
		return item, err
	}
}

func (r *DBConn) GetTaskListsByName(name string) ([]TaskList, error) {
	rows, err := r.Conn.Query("SELECT * FROM lists WHERE")
	if err != nil {
		return []TaskList{}, err
	}

	var lists []TaskList
	for rows.Next() {
		var list TaskList
		err := rows.Scan(&list.Id, &list.Name, &list.Tasks)
		if err != nil {
			return lists, err
		}
		lists = append(lists, list)
	}
	return lists, nil

}

func (r *DBConn) DeleteTaskList(id uint64) error {
	query := `DELETE FROM lists WHERE id = $1;`
	_, err := r.Conn.Exec(query, id)
	switch err {
	case sql.ErrNoRows:
		return fmt.Errorf("no matching record")
	default:
		return err
	}

}

func (r *DBConn) AddTaskToListById(listId uint64, taskId uint64) error {
	query := `UPDATE lists l SET tasks = (l.tasks || $1) WHERE id = $2;`
	err := r.Conn.QueryRow(query, taskId, listId).Scan()
	switch err {
	case sql.ErrNoRows:
		return fmt.Errorf("no matching record")
	default:
		return err
	}
}
