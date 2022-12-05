package model

import (
	"database/sql"
	"fmt"
	"log"
	"os"
	"time"

	_ "github.com/lib/pq"
)

type DBConn struct {
	Conn *sql.DB
}

const (
	HOST = "postgresql"
	PORT = 5432
)

func NewDBConn() (DBConn, error) {
	user := os.Getenv("POSTGRES_USER")
	pass := os.Getenv("POSTGRES_PASSWORD")
	psdb := os.Getenv("POSTGRES_DB")

	dsn := fmt.Sprintf("host=%s port=%d user=%s password=%s dbname=%s sslmode=disable",
		HOST, PORT, user, pass, psdb)
	time.Sleep(10 * time.Second)
	conn, err := sql.Open("postgres", dsn)
	if err != nil {
		return DBConn{}, err
	}

	if err := conn.Ping(); err != nil {
		return DBConn{}, err
	}
	log.Println("Database connection established")
	return DBConn{Conn: conn}, nil

}
