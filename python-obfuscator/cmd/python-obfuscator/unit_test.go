package main

import (
	"bufio"
	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
	"gopkg.in/yaml.v3"
	"io/ioutil"
	"os"
	"os/exec"
	"testing"
)

// Manifest
type Manifest struct {
	FunctionalityTests []FunctionalityTests `yaml:"functionality_tests"`
}

// FunctionalityTests
type FunctionalityTests struct {
	Script string `yaml:"script"`
	Args   string `yaml:"args"`
}

func launchPythonScript(script, args string) (string, error) {
	cmd := exec.Command("python3", script)

	argReader, err := os.Open(args)
	if err != nil {
		return "", err
	}
	defer func() {
		_ = argReader.Close()
	}()
	cmd.Stdin = bufio.NewReader(argReader)

	out, err := cmd.Output()

	if err != nil {
		return "", err
	}

	return string(out), nil
}

func testFunctionality(t *testing.T, input, argsFile string) {
	t.Helper()

	output, err := os.CreateTemp("tests", "*-obfuscator-out.py")
	require.NoError(t, err)
	defer func() {
		_ = os.Remove(output.Name())
	}()

	require.NoError(t, launchObfuscator(input, output.Name(), false))

	expectedOut, expectedErr := launchPythonScript(input, argsFile)
	actualOut, actualErr := launchPythonScript(output.Name(), argsFile)

	if expectedErr != nil {
		assert.Error(t, actualErr)
	} else {
		assert.NoError(t, actualErr)
		assert.Equal(t, expectedOut, actualOut)
	}

}

func functionalityTests(t *testing.T, tests []FunctionalityTests) {
	t.Helper()

	for _, test := range tests {
		t.Run(test.Script, func(t *testing.T) {
			testFunctionality(t, "tests/"+test.Script, "tests/"+test.Args)
		})
	}
}

func TestByManifest(t *testing.T) {
	manifestContents, err := ioutil.ReadFile("tests/manifest.yaml")
	require.NoError(t, err)

	var manifest Manifest
	require.NoError(t, yaml.Unmarshal(manifestContents, &manifest))

	// Functionality Tests
	functionalityTests(t, manifest.FunctionalityTests)
}
