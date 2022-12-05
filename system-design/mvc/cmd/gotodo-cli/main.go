package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"log"
	"net/http"

	"gotodo/pkg/protocol/list"
	"gotodo/pkg/protocol/task"

	"github.com/spf13/cobra"
)

var rootCmd = &cobra.Command{
	Use:   "gotodo-cli",
	Short: "GoToDo CLI View",
	Long:  `GoToDo Command Line Interface to view your ToDo lists and finally Get Things Done.`,
}

var url string
var port int

func request[R any](request *R, endpoint string) func(*cobra.Command, []string) {
	result := func(cmd *cobra.Command, args []string) {
		body, err := json.Marshal(request)
		if err != nil {
			log.Fatalf("unable to marshall request: %v\n", err)
		}
		bodyBuffer := bytes.NewBuffer(body)

		path := fmt.Sprintf("http://%s:%d/%s", url, port, endpoint)

		resp, err := http.Post(path, "application/json", bodyBuffer)
		if err != nil {
			log.Fatalf("unable to make request: %v\n", err)
		}

		log.Printf("got response: %v", resp)
	}

	return result
}

var listCmd = &cobra.Command{
	Use:   "list",
	Short: "Commands to deal with ToDo lists",
}

var listCreateRequest list.CreateRequest
var listCreateCmd = &cobra.Command{
	Use: "create",
	Run: request(&listCreateRequest, "list/create"),
}

var listGetByIdRequest list.GetByIdRequest
var listGetByIdCmd = &cobra.Command{
	Use: "get-by-id",
	Run: request(&listGetByIdRequest, "list/get/id"),
}

var listGetByNameRequest list.GetByNameRequest
var listGetByNameCmd = &cobra.Command{
	Use: "get-by-name",
	Run: request(&listGetByNameRequest, "list/get/name"),
}

var taskCmd = &cobra.Command{
	Use:   "task",
	Short: "Command to deal with individual tasks",
}

var taskCreateRequest task.CreateRequest
var taskCreateCmd = &cobra.Command{
	Use: "create",
	Run: request(&taskCreateRequest, "task/create"),
}

var taskGetByIdRequest task.GetByIdRequest
var taskGetByIdCmd = &cobra.Command{
	Use: "get-by-id",
	Run: request(&taskGetByIdRequest, "task/get/id"),
}

var taskGetByNameRequest task.GetByNameRequest
var taskGetByNameCmd = &cobra.Command{
	Use: "get-by-name",
	Run: request(&taskGetByNameRequest, "task/get/name"),
}

var taskUpdateRequest task.UpdateRequest
var taskUpdateCmd = &cobra.Command{
	Use: "update",
	Run: request(&taskUpdateRequest, "task/update"),
}

var taskAddToListRequest task.AddToListRequest
var taskAddToListCmd = &cobra.Command{
	Use: "add-to-list",
	Run: request(&taskAddToListRequest, "task/AddToList"),
}

func setStructure() {
	rootCmd.AddCommand(listCmd, taskCmd)
	listCmd.AddCommand(listCreateCmd, listGetByIdCmd, listGetByNameCmd)
	taskCmd.AddCommand(taskCreateCmd, taskGetByIdCmd, taskGetByNameCmd, taskUpdateCmd, taskAddToListCmd)
}

func setArguments() {
	rootCmd.PersistentFlags().StringVarP(&url, "url", "u", "127.0.0.1", "Specifies the url of GoToDo server to connect to.")
	rootCmd.PersistentFlags().IntVarP(&port, "port", "p", 8080, "Specifies the port of GoToDo server.")
	requireServer := func(cmd *cobra.Command) {
		cmd.MarkFlagRequired("url")
		cmd.MarkFlagRequired("port")
	}

	requireServer(listCmd)
	requireServer(taskCmd)

	listCreateCmd.Flags().StringVar(&listCreateRequest.Name, "name", "", "specify a name for list")
	listGetByIdCmd.Flags().Uint64Var(&listGetByIdRequest.Id, "id", 0, "specify an id of list")
	listGetByNameCmd.Flags().StringVar(&listGetByNameRequest.Name, "name", "", "specify a name of list")

	taskCreateCmd.Flags().StringVar(&taskCreateRequest.Name, "name", "", "specify a name for task")
	taskCreateCmd.Flags().StringVar(&taskCreateRequest.Description, "desc", "", "specify a description for task")
	taskGetByIdCmd.Flags().Uint64Var(&taskGetByIdRequest.Id, "id", 0, "specify an id of task")
	taskGetByNameCmd.Flags().StringVar(&taskGetByNameRequest.Name, "name", "", "specify a name of task")
	taskUpdateCmd.Flags().Uint64Var(&taskUpdateRequest.Id, "id", 0, "specify an id of task")
	//taskUpdateCmd.Flags().IntVar(&taskUpdateRequest.To, "to", 0, "specify stage to update to")
	taskAddToListCmd.Flags().Uint64Var(&taskAddToListRequest.TaskId, "tid", 0, "specify an id of task")
	taskAddToListCmd.Flags().Uint64Var(&taskAddToListRequest.ListId, "lid", 0, "specify an id of list")
}

func init() {
	setStructure()
	setArguments()
}

func main() {
	if err := rootCmd.Execute(); err != nil {
		log.Fatal(fmt.Errorf("unable to execute command: %v", err))
	}
}
