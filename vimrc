" All system-wide defaults are set in $VIMRUNTIME/debian.vim and sourced by
" the call to :runtime you can find below.  If you wish to change any of those
" settings, you should do it in this file (/etc/vim/vimrc), since debian.vim
" will be overwritten everytime an upgrade of the vim packages is performed.
" It is recommended to make changes after sourcing debian.vim since it alters
" the value of the 'compatible' option.

" This line should not be removed as it ensures that various options are
" properly set to work with the Vim-related packages available in Debian.
runtime! debian.vim

" Uncomment the next line to make Vim more Vi-compatible
" NOTE: debian.vim sets 'nocompatible'.  Setting 'compatible' changes numerous
" options, so any other options should be set AFTER setting 'compatible'.
"set compatible

" Vim5 and later versions support syntax highlighting. Uncommenting the next
" line enables syntax highlighting by default.
if has("syntax")
  syntax on
endif

" If using a dark background within the editing area and syntax highlighting
" turn on this option as well
"set background=dark

" Uncomment the following to have Vim jump to the last position when
" reopening a file
"if has("autocmd")
"  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
"endif

" Uncomment the following to have Vim load indentation rules and plugins
" according to the detected filetype.
"if has("autocmd")
"  filetype plugin indent on
"endif

" The following are commented out as they cause vim to behave a lot
" differently from regular Vi. They are highly recommended though.
"set showcmd		" Show (partial) command in status line.
"set showmatch		" Show matching brackets.
"set ignorecase		" Do case insensitive matching
"set smartcase		" Do smart case matching
"set incsearch		" Incremental search
"set autowrite		" Automatically save before commands like :next and :make
"set hidden		" Hide buffers when they are abandoned
"set mouse=a		" Enable mouse usage (all modes)

" Source a global configuration file if available
if filereadable("/etc/vim/vimrc.local")
  source /etc/vim/vimrc.local
endif
"syntax high light
syntax on
"show the line number
set nu
"为c程序提供自动缩进
set smartindent
"使用c程序的自动缩进
set cindent
"设置缩进的空格数为4
set shiftwidth=4
"设置制表符
set tabstop=4
set softtabstop=4
"匹配模式（）
set showmatch
"不保留备份文件
set nobackup
"配色方案
"colorscheme delek
"中文显示
set fileencodings=utf-8,gb2312,gbk,gb18030
set termencoding=utf-8
set encoding=utf-8
"字体
"自动插入头文件
autocmd BufNewFile *.cpp,*.py,*.java,*.html,*.php  exec ":call SetTitle()"
func SetTitle()
	if(&filetype=='php')
	call setline(1,"<!-- *********************************************************")
	call append(line("."),"  file name: ".expand("%")."")
	call append(line(".")+1,"  author : kereo")
	call append(line(".")+2,"  create time:  ".strftime("%c")."")
	call append(line(".")+3,"********************************************************* -->")
	call append(line(".")+4,"<?php")
	call append(line(".")+5,'	header("Content-type: text/html;  charset=utf-8");')
	endif
	if(&filetype == 'html')
	call setline(1,"<!-- ********************************************************* ")
	call append(line("."),"  file name: ".expand("%")."")
	call append(line(".")+1,"  author : kereo ")
	call append(line(".")+2,"  create time:  ".strftime("%c")."")
	call append(line(".")+3," ********************************************************* -->")	
	call append(line(".")+4,"<!DOCTYPE html>")
	call append(line(".")+5,'<html lang="en">')
	call append(line(".")+6,"	<head>")
	call append(line(".")+7,'		<meta charset="utf-8">')
	call append(line(".")+8,'		<meta http-equiv="X-UA-Compatible" content="IE=edge">')
	call append(line(".")+9,'		<meta name="viewport" content="width=device-width, initial-scale=1">')
	call append(line(".")+10,'		<link href="bootstrap.css" rel="stylesheet">')
	call append(line(".")+11,'		<link rel="stylesheet" href="http://netdna.bootstrapcdn.com/bootstrap/3.1.1/css/bootstrap.min.css">')
	call append(line(".")+12,'		<script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>')
	call append(line(".")+13,'		<script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>')
	call append(line(".")+14,' 	</head>')
	call append(line(".")+15,'	<body>')
	call append(line(".")+16,'		<script src="jquery.js"></script>')
	call append(line(".")+17,'		<script src="bootstrap.js"></script>')
	call append(line(".")+18,'		<script src="http://libs.baidu.com/jquery/1.9.0/jquery.min.js"></script>')
	call append(line(".")+19,'		<script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.2.0/js/bootstrap.min.js"></script>')
	call append(line(".")+20,'	</body>')
	call append(line(".")+21,'</html>')
	endif
	if(&filetype == 'cpp')
	call setline(1,"/*********************************************************")
	call append(line("."),"  file name: ".expand("%")."")
	call append(line(".")+1,"  author : Sakura_Mashiro")
	call append(line(".")+2,"  create time:  ".strftime("%c")."")
	call append(line(".")+3,"**********************************************************")
	call append(line(".")+4,"solution:")
	call append(line(".")+5,"**********************************************************/")
	call append(line(".")+6,"#include<iostream>")
	call append(line(".")+7,"#include<cstdio>")
	call append(line(".")+8,"#include<cstring>")
	call append(line(".")+9,"#include<queue>")
	call append(line(".")+10,"#include<set>")
	call append(line(".")+11,"#include<map>")
	call append(line(".")+12,"#include<vector>")
	call append(line(".")+13,"#include<stack>")
	call append(line(".")+14,"#include<cmath>")
	call append(line(".")+15,"#include<string>")
	call append(line(".")+16,"#include<algorithm>")
	call append(line(".")+17,"using namespace std;")
	call append(line(".")+18,"typedef long long ll;")
	call append(line(".")+19,"typedef unsigned long long ull;")
	call append(line(".")+20,"const int sigma_size=26;")
	call append(line(".")+21,"const int N=100+50;")
	call append(line(".")+22,"const int MAXN=100000+50;")
	call append(line(".")+23,"const int inf=0x3fffffff;")
	call append(line(".")+24,"const double eps=1e-8;")
	call append(line(".")+25,"const int HASH=100007;")
	call append(line(".")+26,"const int mod=1000000000+7;")
	call append(line(".")+27,"#define L(x) (x<<1)")
	call append(line(".")+28,"#define R(x) (x<<1|1)")
	call append(line(".")+29,"#define Ls(x) (x->ch[0])")
	call append(line(".")+30,"#define Rs(x) (x->ch[1])")
	call append(line(".")+31,"#define PII pair<int, int>")
	call append(line(".")+32,"#define mk(x,y) make_pair((x),(y))")
	call append(line(".")+33,"#define REP(i,a,b) for(int i=(int)a;i<=(int)b;i++)")
	call append(line(".")+34,"#define REPF(i,a,b) for(int i=(int)a;i>=(int)b;i--)")
	call append(line(".")+35,"template<class T>")
	call append(line(".")+36,"inline bool RD(T & res){")
	call append(line(".")+37,"	char c;")
	call append(line(".")+38,"	int sgn;")
	call append(line(".")+39,"	if(c=getchar(),c == EOF) return 0;")
	call append(line(".")+40,"	while(c!='-' && (c<'0' || c>'9')) c=getchar();")
	call append(line(".")+41,"	sgn=(c == '-') ? -1 : 1;")
	call append(line(".")+42,"	res=(c == '-') ? 0 : c-'0';")
	call append(line(".")+43,"	while(c=getchar(),c>='0' && c<='9') res=res*10+(c-'0');")
	call append(line(".")+44,"	res*=sgn;")
	call append(line(".")+45,"	return 1;")
	call append(line(".")+46,"}")
	call append(line(".")+47,"template<class T>")
	call append(line(".")+48,"inline void PT(T x){")
	call append(line(".")+49,"	if(x < 0){")
	call append(line(".")+50,"		putchar('-');")
	call append(line(".")+51,"		x=-x;")
	call append(line(".")+52,"	}")
	call append(line(".")+53,"	if(x > 9) PT(x/10);")
	call append(line(".")+54,"	putchar(x % 10 + '0');")
	call append(line(".")+55,"}")
	call append(line(".")+56,"int main(){")
	call append(line(".")+57,"	return 0;")
	call append(line(".")+58,"}")
	endif
	if(&filetype == 'python')
	call setline(1,"#!/usr/bin/env python")
	call append(line("."),"# -*- coding: utf-8 -*-")
	call append(line(".")+1,"#*********************************************************")
	call append(line(".")+2,"#  file name: ".expand("%")."")
	call append(line(".")+3,"#  author : kereo")
	call append(line(".")+4,"#  create time:  ".strftime("%c")."")
	call append(line(".")+5,"#*********************************************************")
	endif
	if(&filetype == 'java')
	call setline(1,"/* ********************************************************")
	call append(line("."),"  file name: ".expand("%")."")
	call append(line(".")+1,"  author : kereo")
	call append(line(".")+2,"  create time:  ".strftime("%c")."")
	call append(line(".")+3,"*********************************************************/")
	call append(line(".")+4,"import java.io.*;")
	call append(line(".")+5,"import java.math.BigInteger;")
	call append(line(".")+6,"import java.util.*;")
	endif
	autocmd BufNewFile * normal G
endfunc
map <F9> :call CompileRunGcc()<CR>
func! CompileRunGcc()
	 exec "w"
	if &filetype == 'c'
		 exec "!g++ % -o %<"
		 exec "! ./%<"
	elseif &filetype == 'cpp'
		 exec "!g++ % -o a"
         exec "! ./a"
    elseif &filetype == 'java' 
		 exec "!javac %" 
		 exec "!java %<"
	elseif &filetype == 'sh'
		 :! bash %
    elseif &filetype == 'python'
         exec "! python2.7 %"
		 endif
endfunc
inoremap ' ''<ESC>i
inoremap " ""<ESC>i
inoremap { {}<ESC>i
