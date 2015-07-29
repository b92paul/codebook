#!/usr/bin/env python
doc_class = '\\documentclass[10pt,twocolumn,oneside]{article}'
head = '''\\usepackage[T1]{fontenc}
\\usepackage{amsmath, courier, listings, fancyhdr, graphicx}
\\topmargin=0pt
\\headsep=5pt
\\textheight=750pt
\\footskip=0pt
\\voffset=-40pt
\\textwidth=520pt
\\marginparsep=0pt
\\marginparwidth=0pt
\\marginparpush=0pt
\\oddsidemargin=0pt
\\evensidemargin=0pt
\\hoffset=-30pt
 
\\lstset{
	language=C,
	basicstyle=\\tt,
	breaklines=true,
	tabsize=2
}
 
\\begin{document}
\\pagestyle{fancy}
\\fancyfoot{}
\\fancyfoot[R]{\\includegraphics[width=20pt]{taipei-hot.jpg}}
\\fancyhead[L]{Taipei-Hot, National Taiwan University}
\\fancyhead[R]{\\thepage}
\\renewcommand{\\headrulewidth}{0.4pt}
\\renewcommand{\\contentsname}{Contents} 

\\scriptsize
\\tableofcontents
'''
tail = '\\end{document}'
src_types = ['.c', '.C', '.cpp', '.CPP', '.vimrc']
import os
import sys
import subprocess
outname = 'book_short.tex'
sys.stdout = open(outname, 'w')
print doc_class
print head
for root, dirs, files in os.walk('..'):
  if root.find('.svn') >= 0:
    continue
  secname = os.path.basename(root)
  if secname.startswith('.'):
    continue
  print '\\section{' + secname + '}'
  for name in files:
    base, ext = os.path.splitext(name)
    if ext not in src_types and name <> '.vimrc':
      continue
    if base.startswith('!'):
	  continue
    print '\\subsection{' + base + '}'
    print '\\begin{lstlisting}'
    f = open(root + '/' + name)
    print f.read()
    f.close()
    print '\\end{lstlisting}'
print tail
sys.stdout.flush()
sys.stdout.close()
subprocess.call(['xelatex', outname])

