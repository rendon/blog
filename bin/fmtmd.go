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
//     <span class='publication'><span class="fa-solid fa-clock"></span> <em>2024-05-04</em></span>
//     <span class='tags'><span class="fa-solid fa-tag"></span><code>#dev</code> <code>#aws</code></span>
// </p>
// ...


package main

import (
	"log"
	"bufio"
	"strings"
	"fmt"
	"os"
	"io"
)

const format = `
<p class='metadata'>
    <span class='publication'><span class="fa-solid fa-clock"></span> <em>%s</em></span>
    <span class='tags'><span class="fa-solid fa-tag"></span>%s</span>
</p>
`

func formatMetadata(line string) string {
	// len("<p></p>") == 7
	if len(line) < 7 {
		return ""
	}
	text := line[3:len(line)-4]
	tokens := strings.Split(text, " ")
	date := tokens[0]
	var tags []string
	for i := 2; i < len(tokens); i++ {
		tags = append(tags, fmt.Sprintf("<code>%s</code>", tokens[i]))
	}

	return fmt.Sprintf(format, date, strings.Join(tags, " "))
}

func main() {
	in := bufio.NewReader(os.Stdin)
	buf, err := io.ReadAll(in)
	if err != nil {
		log.Fatalf("unable to read input: %s", err)
	}
	lines := strings.Split(string(buf), "\n")
	done := false
	for i := 0; i < len(lines); i++ {
		fmt.Println(lines[i])
		// The first line with 
		if !done && strings.HasPrefix(lines[i], "<h1") {
			if i + 1 < len(lines) {
				fmt.Println(formatMetadata(lines[i+1]))
				i++
				done = true
			}
		}
	}
}
