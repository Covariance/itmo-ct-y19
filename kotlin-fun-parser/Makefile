# Project directory
ROOT := $(shell pwd)

##@ General

# The help target prints out all targets with their descriptions organized
# beneath their categories. The categories are represented by '##@' and the
# target descriptions by '##'. The awk commands is responsible for reading the
# entire set of makefiles included in this invocation, looking for lines of the
# file as xyz: ## something, and then pretty-format the target and help. Then,
# if there's a line with ##@ something, that gets pretty-printed as a category.
# More info on the usage of ANSI control characters for terminal formatting:
# https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_parameters
# More info on the awk command:
# http://linuxcommand.org/lc3_adv_awk.php

help: ## Display this message.
	@awk 'BEGIN { \
		FS = ":.*##";\
		printf "Usage:\n  make \033[36m<target>\033[0m\n" \
		} \
		/^[a-zA-Z_0-9-]+:.*?##/ \
		{ \
		printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 \
		} \
		/^##@/ \
		{ \
		printf "\n\033[1m%s\033[0m\n", substr($$0, 5) \
		}' $(MAKEFILE_LIST)


##@ Development
fmt: ## Run go fmt against code.
	go fmt ./...

vet: ## Run go vet against code.
	go vet ./...

lint: ensure-linter ## Run golangci-lint (https://golangci-lint.run/) against code.
	$(GOLANGCI-LINT) run ./... --verbose

test: fmt vet lint ## Run tests for this connector and common packages.
	go test ./... -coverprofile cover.out

##@ Build

local-build-unsafe: ## Build binary locally without testing.
	go build -o ./bin/manager ./cmd/kotlin-fun-parser/main.go

local-build: test local-build-unsafe ## Build binary locally.

##@ Dependencies

GOLANGCI-LINT := $(ROOT)/bin/golangci-lint ## Location of golangci-lint binary
ensure-linter: ## Download golangci-lint if necessary.
	@if [ ! -x "$(command -v golangci-lint)" ] && [ ! -x $(GOLANGCI-LINT) ]; \
 	then \
  		curl -sSfL https://raw.githubusercontent.com/golangci/golangci-lint/master/install.sh \
                         | sh -s -- -b $(ROOT)/bin v1.43.0; \
  	fi