<style>
@media print {
  .markdown-body {
    font-size: 10pt;
    margin: 0;
  }
  .markdown-body code { background-color: #fff; }
}
.markdown-body {
  font-family: Palatino;
  line-height: 1.2;
}
.markdown-body hr {
  height: 2pt;
  background-color: #212121;
}
.preview.wrapper, #preview.cover { padding: 0; }

.page {
  page-break-after: auto;
  page-break-inside: avoid;
  position: relative;
  padding: 1.5cm 1cm;
}
.content > p {
  text-indent: 1cm;
  text-align: justify;
}
.col.half {
  width: 49.6%;
  display: inline-block;
  vertical-align: top;
}
.col.half.left {   padding-right: 0.25cm; }
.col.half.right {   padding-left: 0.25cm; }
.page-num {
  position: absolute;
  top: 0.5cm;
  right: 1cm;
}
</style>

<div class="page">
<center>

### <big>Stepper-motor-controlled Positioning Goniometer</big><br>with Automatic Laser beam Detection

<big>Shivaprasad V</big>

PH18C032\
_1<sup>st</sup> Year M.Sc. Physics\
Indian Institute of Technology\
Madras_

(Dated: November 14, 2018)
</center>

**Abstract:** An article usually includes an abstract, a concise summary of the work covered at length in the main body of the article.

Usage: Secondary publications and information retrieval purposes.
Structure: You may use the description environment to structure your abstract; use the optional argument of the \item command to give the category of each item.

<div class="left half col content">
<center>

#### I. FIRST-LEVEL HEADING
</center>

This sample document demonstrates proper use of REVTEX 4.1 (and LATEX 2ε) in mansucripts prepared for submission to APS journals. Further information can be found in the REVTEX 4.1 documentation included in the distribution or available at http://authors.aps.org/ revtex4/.

When commands are referred to in this example file, they are always shown with their required arguments, using normal TEX format. In this format, #1, #2, etc. stand for required author-supplied arguments to com- mands. For example, in \section{#1} the #1 stands for the title text of the author’s section heading, and in \title{#1} the #1 stands for the title text of the paper.

Line breaks in section headings at all levels can be in- troduced using \\. A blank input line tells TEX that the paragraph has ended. Note that top-level section head- ings are automatically uppercased. If a specific letter or word should appear in lowercase instead, you must escape it using \lowercase{#1} as in the word “via” above.

---
<div>

∗ A footnote to the article title\
† Also at Physics Department, XYZ University.\
</div>
</div>

<div class="right half col content">
<center>

#### A. Second-level heading: Formatting
</center>

This file may be formatted in either the preprint or reprint style. reprint format mimics final journal out- put. Either format may be used for submission purposes. letter sized paper should be used when submitting to APS journals.

_1. Wide text (A level-3 head)_

The widetext environment will make the text the width of the full page, as on page ??. (Note the use the \pageref{#1} command to refer to the page number.)
a. Note (Fourth-level head is run in) The width- changing commands only take effect in two-column for- matting. There is no effect if text is in a single column.

<center>

#### B. Citations and References
</center>

A citation in text uses the command \cite{#1} or \onlinecite{#1} and refers to an entry in the bibliog- raphy. An entry in the bibliography is a reference to another document.

_1. Citations_

Because REVTEX uses the natbib package of Patrick Daly, the entire repertoire of commands in that package
</div>

</div> <!--page 1-->

<div class="page">
<div class="left half col content">

are available for your document; see the natbib docu- mentation for further details. Please note that REVTEX requires version 8.31a or later of natbib.

_a. Syntax:_ The argument of `\cite` may be a single key, or may consist of a comma-separated list of keys. The citation key may contain letters, numbers, the dash (-) character, or the period (.) character. New with natbib 8.3 is an extension to the syntax that allows for a star (*) form and two optional arguments on the citation key itself. The syntax of the `\cite` command is thus (informally stated)

```\cite { key }, or
\cite { optarg+key }, or
\cite { optarg+key , optarg+key...},
where optarg+key signifies
key, or *key, or
[pre]key, or [pre][post]key, or even *[pre ][post ]key.
```

where pre and post is whatever text you wish to place at the beginning and end, respectively, of the bibliographic reference (see Ref. [? ] and the two under Ref. [? ]). (Keep in mind that no automatic space or punctuation is applied.) It is highly recommended that you put the
</div>

<div class="right half col content">

entire pre or post portion within its own set of braces, for example: \cite { [ {text }]key }. The extra set of braces will keep LATEX out of trouble if your text contains the comma (,) character.
The star (*) modifier to the key signifies that the ref- erence is to be merged with the previous reference into a single bibliographic entry, a common idiom in APS and AIP articles (see below, Ref. [? ]). When references are merged in this way, they are separated by a semicolon instead of the period (full stop) that would otherwise ap- pear.
b. Eliding repeated information When a reference is merged, some of its fields may be elided: for example, when the author matches that of the previous reference, it is omitted. If both author and journal match, both are omitted. If the journal matches, but the author does not, the journal is replaced by ibid., as exemplified by Ref. [? ]. These rules embody common editorial practice in APS and AIP journals and will only be in effect if the markup features of the APS and AIP BibTEX styles is employed.
c. The options of the cite command itself Please note that optional arguments to the key change the ref- erence in the bibliography, not the citation in the body of the document. For the latter, use the optional argu- ments of the \cite command itself: \cite *[pre-cite] [post-cite ]{key-list }.

<div class="page-num">2</div>
</div>

</div> <!--page 2-->
