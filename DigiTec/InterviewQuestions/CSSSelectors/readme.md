# Overview

CSS Selectors are an important concept in web browsing. They allow you to separate the data nd presentation in standard HTML 5 and then "select" portions of the data to be displayed in different ways. For this reason a basic understanding of CSS is important for any web developer who wishes to do more than make the most simple pages. Some web developers have even gone so far as to write their own selector processing engines, with jQuery being the crowning example, in place of the ones already provided by the web browser itself. This problem centers on the first steps in a selectors engine. Parsing and storing the selectors in a way that would allow for efficient matching against a document language.

# Problem Description

You are given the problem of implementing a very basic subset of CSS seletors. Specifically you must match basic tag tokens which can be any arbitrary string of the characters a through z (you can assume all input is lower case for easy of implementation). CSS allows composition of tags to represent matching a nodes parent chain. So you will need to be able to handle building an arbitrarily complex hierarchy. In addition CSS supports a concept called combinators that describe the relationship between two tags, whether it be ancestor matching (no combinator), sibling matches (+ combinator) or the direct child combinator (>). Following will be a set of data that demonstrates the various edge conditions you will be expected to handle.

Your goal is to describe a structure to store the parsed selectors that you could later use for matching against a tree. Further, you will be taking in selectors as strings and so you'll have to process them into your own internal format.

# Data

## Basic
```cpp
"div"
"p"
"arbitrarytagname"
```

## Whitespace
```cpp
// Leading space
"  div" 

// Trailing space
"p  "
```

## Combinators
```cpp
"div p"
"div + p"
"div > child"
"div + p > ul"
"div p + ul > li"

// Variations on whitespace
"div+p"
"div  +p"
```
