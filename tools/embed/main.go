package main

import (
	"io"
	"fmt"
	"log"
	"path"
	"os"
	"regexp"
	"strings"
)

func exists(fn string) bool {
	if _, err := os.Stat(fn); err == nil {
		return true
	}
	return false
}

func main() {
	log.SetFlags(0)

	buf, err := io.ReadAll(os.Stdin)
	if err != nil {
		log.Fatalf("unable to read file: %s", err)
	}

	re := regexp.MustCompile("^Embed: `")
	lines := strings.Split(strings.Trim(string(buf), "\n"), "\n")
	for _, line := range lines {
		if !re.MatchString(line) {
			fmt.Println(line)
			continue
		}

		file := line[8:len(line)-1]
		if !exists(file) {
			log.Printf("file %s does not exist", file)
			// Will have to replace manually
			continue
		}
		body, err := os.ReadFile(file)
		if err != nil {
			log.Printf("unable to read file %s: %s", file, err)
			// Will have to replace manually
			continue
		}

		var ext string
		if len(path.Ext(file)) > 0 {
			ext = path.Ext(file)[1:]
		}
		fmt.Printf("\n```%s\n%s\n```\n", ext, body)

		if err := os.Remove(file); err != nil {
			log.Printf("unable to delete file %s: %s", file, err)
			continue
		}
	}

}
