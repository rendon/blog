// Converts Wiki links ([[text]]) to Markdown links ([text](/text)).
package main

import (
	"bufio"
	"bytes"
	"fmt"
	"io"
	"log"
	"os"
	"regexp"
	"strings"
)

func convertLinks(text string) string {
	text = strings.ReplaceAll(text, "[[", "[")
	text = strings.ReplaceAll(text, "]]", "]")
	start := -1
	var buf bytes.Buffer
	for i, c := range text {
		if c == '[' {
			start = i
		} else if c == ']' {
			link := text[start+1:i]
			buf.WriteString(fmt.Sprintf("[%s](/%s)", link, link))
			start = -1
		} else if start == -1 {
			buf.WriteRune(c)
		}
	}

	return buf.String()
}

func main() {
	in := bufio.NewReader(os.Stdin)
	buf, err := io.ReadAll(in)
	if err != nil {
		log.Fatalf("unable to read input: %s", err)
	}
	lines := strings.Split(string(buf), "\n")

	re := regexp.MustCompile(`(\[\[(.*)\]\])+`)
	for i := 0; i < len(lines); i++ {
		if re.MatchString(lines[i]) {
			fmt.Println(convertLinks(lines[i]))
		} else {
			fmt.Println(lines[i])
		}
	}
}
