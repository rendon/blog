// Finds the first paragram after the title and converts the second
// line of an HTML document into a metadata header.
// From
// <h1...>Title</h1>
// <p>2024-05-04 14:24:01 #dev #aws>
// ...
//
// To
// <h1...>Title</h1>
// <p class='metadata'>
//     <span class='published'><span class="fa-solid fa-clock"></span> <em>2024-05-04</em></span>
//     <span class='tags'><span class="fa-solid fa-tag"></span><code>#dev</code> <code>#aws</code></span>
// </p>
// ...
//
// TODO: Parse metadata in yaml format instead. The output should ramain unchanged.
//
// Posts store metadata at the beginning of the file within `---` and `---`. For example:
// ---
// tags:
//     - aws
//     - dev
//     - post
// created: 2024-05-14
// ---
//
// # Set up AWS credentials

package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
	"regexp"
	"strings"

	"gopkg.in/yaml.v3"
)

const format = `
    
</p>
`

type Metadata struct {
	Tags []string `yaml:"tags"`
	Created string `yaml:"created"`
	Updated string `yaml:"updated"`
}

func isDate(text string) bool {
	match, err := regexp.MatchString(`\d\d\d\d-\d\d-\d\d`, text)
	return err == nil && match
}

func printMetadata(md *Metadata) {
	if md == nil {
		return
	}
	fmt.Println("<p class='metadata'>")
	fmt.Printf("<span class='published'><span class='fa-solid fa-clock-rotate-left'></span> <em>%s</em></span>\n", md.Created)
	if len(md.Updated) > 0 {
		fmt.Printf("<span class='updated'><span class='fa-solid fa-clock-rotate-left'></span> <em>%s</em></span>\n", md.Updated)
	}
	var tags []string
	for _, tag := range md.Tags {
		tags = append(tags, fmt.Sprintf("<code>%s</code>", tag))
	}
	fmt.Printf("<span class='tags'><span class='fa-solid fa-tag'></span>%s</span>\n", strings.Join(tags, ""))
	fmt.Println("</p>")
}

func extractMetadata(body string) (*Metadata, []string) {
	lines := strings.Split(body, "\n")
	startLine := -1
	endLine := -1
	for i, line := range lines {
		if line == "---" {
			if startLine == -1 {
				startLine = i
			} else if endLine == -1 {
				endLine = i
			} else {
				break
			}
		}
	}

	if startLine >= 0 && endLine >= 0 {
		mdtext := strings.Join(lines[startLine+1:endLine], "\n")
		var md Metadata
		if err := yaml.Unmarshal([]byte(mdtext), &md); err != nil {
			log.Printf("error: %s", err)
			return nil, lines
		}
		return &md, append(lines[:startLine], lines[endLine+1:]...)
	}
	return nil, lines
}

func main() {
	in := bufio.NewReader(os.Stdin)
	buf, err := io.ReadAll(in)
	if err != nil {
		log.Fatalf("unable to read input: %s", err)
	}

	md, lines := extractMetadata(string(buf))
	for _, line := range lines {
		fmt.Println(line)
		if strings.HasPrefix(line, "# ") {
			printMetadata(md)
		}
	}
}
