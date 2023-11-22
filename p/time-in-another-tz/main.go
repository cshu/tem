package main

import (
	"bufio"
	"flag"
	"fmt"
	rs "github.com/cshu/golangrs"
	"os"
	"regexp"
	"strconv"
	"strings"
	"time"
)

// var xclipfl = flag.Bool("xclip", true, "Try to copy result to clipboard via xclip")//todo
var fromfl = flag.String("from", "", "From TZ IDENTIFIER, e.g. America/New_York")
var tofl = flag.String("to", "", "To TZ IDENTIFIER, e.g. America/Vancouver")
var frommonthfl = flag.String("from-month", "", "From MONTH, e.g. 11")
var fromyearfl = flag.String("from-year", "", "From YEAR, e.g. 2023")

func main() {
	flag.Parse()
	if flag.NArg() != 0 {
		panic(`Unexpected arguments.`)
	}
	//sbuf := flag.Args()
	var err error
	if *fromfl == "" {
		panic(`Must specify "-from" TZ IDENTIFIER`)
	}
	fromloc, err := time.LoadLocation(*fromfl)
	rs.CheckErr(err)
	if *tofl == "" {
		panic(`Must specify "-to" TZ IDENTIFIER`)
	}
	toloc, err := time.LoadLocation(*tofl)
	rs.CheckErr(err)
	timenow := time.Now()
	var timeBuf time.Time
	var y, m, d int
	if *fromyearfl == "" {
		timeBuf = timenow.In(fromloc)
		y = timeBuf.Year()
	} else {
		y, err = strconv.Atoi(*fromyearfl)
		rs.CheckErr(err)
	}
	if *frommonthfl == "" {
		timeBuf = timenow.In(fromloc)
		m = int(timeBuf.Month())
	} else {
		m, err = strconv.Atoi(*frommonthfl)
		rs.CheckErr(err)
	}
	//
	scanner := bufio.NewScanner(os.Stdin)
	fmt.Print(`Input THE DAY OF THE MONTH or Mon/Tue/... (or empty input for today): `) //todo also allow fetching content from clipboard?
	if !scanner.Scan() {
		panic(`Cannot get input from stdin.`)
	}
	instr := strings.ToLower(strings.TrimSpace(scanner.Text()))
	re := regexp.MustCompile(`[^0-9]`)
	if instr == `` {
		timeBuf = timenow.In(fromloc)
		d = timeBuf.Day()
	} else {
		digits := re.ReplaceAllString(instr, ``)
		if len(digits) != 0 {
			d, err = strconv.Atoi(digits)
			if *fromyearfl == "" && *frommonthfl == "" {
				timeBuf = timenow.In(fromloc)
				for timeBuf.Day() != d {
					timeBuf = timeBuf.AddDate(0, 0, 1)
				}
				y = timeBuf.Year()
				m = int(timeBuf.Month())
			} else {
				//timeBuf = time.Date(y, time.Month(m), d, 0, 0, 0, 0, loc)
			}
		} else {
			if *fromyearfl == "" && *frommonthfl == "" {
				timeBuf = timenow.In(fromloc)
			} else {
				timeBuf = time.Date(y, time.Month(m), 1, 0, 0, 0, 0, fromloc)
			}
			var targetweekday time.Weekday
			switch {
			case strings.HasPrefix(instr, `sun`):
				targetweekday = time.Sunday
			case strings.HasPrefix(instr, `mon`):
				targetweekday = time.Monday
			case strings.HasPrefix(instr, `tue`):
				targetweekday = time.Tuesday
			case strings.HasPrefix(instr, `wed`):
				targetweekday = time.Wednesday
			case strings.HasPrefix(instr, `thu`):
				targetweekday = time.Thursday
			case strings.HasPrefix(instr, `fri`):
				targetweekday = time.Friday
			case strings.HasPrefix(instr, `sat`):
				targetweekday = time.Saturday
			default:
				panic("Cannot parse the day")
			}
			for timeBuf.Weekday() != targetweekday {
				timeBuf = timeBuf.AddDate(0, 0, 1)
			}
			y = timeBuf.Year()
			m = int(timeBuf.Month())
			d = timeBuf.Day()
		}
	}
	//
	fmt.Print(`Input time: `) //todo also allow fetching content from clipboard?
	if !scanner.Scan() {
		panic(`Cannot get input from stdin.`)
	}
	instr = strings.ToLower(strings.TrimSpace(scanner.Text()))
	var H, M, S int
	if instr == `` {
		timeBuf = timenow.In(fromloc)
		H = timeBuf.Hour()
		M = timeBuf.Minute()
		S = timeBuf.Second()
	} else {
		isPM := strings.HasSuffix(instr, `pm`)
		//re = regexp.MustCompile(`[^0-9]`)
		instr = re.ReplaceAllString(instr, ``)
		leninstr := len(instr)
		switch leninstr {
		case 1, 2:
			H, err = strconv.Atoi(instr)
			rs.CheckErr(err)
		case 3:
			H, err = strconv.Atoi(instr[:1])
			rs.CheckErr(err)
			M, err = strconv.Atoi(instr[1:])
			rs.CheckErr(err)
		case 4:
			H, err = strconv.Atoi(instr[:2])
			rs.CheckErr(err)
			M, err = strconv.Atoi(instr[2:])
			rs.CheckErr(err)
		case 5:
			H, err = strconv.Atoi(instr[:1])
			rs.CheckErr(err)
			M, err = strconv.Atoi(instr[1:3])
			rs.CheckErr(err)
			S, err = strconv.Atoi(instr[3:])
			rs.CheckErr(err)
		case 6:
			H, err = strconv.Atoi(instr[:2])
			rs.CheckErr(err)
			M, err = strconv.Atoi(instr[2:4])
			rs.CheckErr(err)
			S, err = strconv.Atoi(instr[4:])
			rs.CheckErr(err)
		default:
			panic(`Input time cannot be parsed.`)
		}
		if H >= 12 {
			//do nothing?
		} else if isPM {
			H += 12
		} else {
			fmt.Print(`Is AM? (Y/n): `)
			if !scanner.Scan() {
				panic(`Cannot get input from stdin.`)
			}
			instr = strings.ToLower(strings.TrimSpace(scanner.Text()))
			if strings.HasPrefix(instr, "n") {
				H += 12
			}
		}
	}
	fromdate := time.Date(y, time.Month(m), d, H, M, S, 0, fromloc)
	todate := fromdate.In(toloc)
	fmt.Println(`####################`)
	fmt.Println(fromdate)
	fmt.Println(`####################`)
	fmt.Println(todate)
	fmt.Println(`####################`)
}
