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
autocmd BufNewFile *.cpp,*.py,*.java exec ":call SetTitle()"
func SetTitle()
	if(&filetype == 'cpp')
	call setline(1,"/*********************************************************")
	call append(line("."),"  file name: ".expand("%")."")
	call append(line(".")+1,"  author : kereo")
	call append(line(".")+2,"  create time:  ".strftime("%c")."")
	call append(line(".")+3,"*********************************************************/")
	call append(line(".")+4,"#include<iostream>")
	call append(line(".")+5,"#include<cstdio>")
	call append(line(".")+6,"#include<cstring>")
	call append(line(".")+7,"#include<queue>")
	call append(line(".")+8,"#include<set>")
	call append(line(".")+9,"#include<map>")
	call append(line(".")+10,"#include<vector>")
	call append(line(".")+11,"#include<stack>")
	call append(line(".")+12,"#include<cmath>")
	call append(line(".")+13,"#include<string>")
	call append(line(".")+14,"#include<algorithm>")
	call append(line(".")+15,"using namespace std;")
	call append(line(".")+16,"typedef long long ll;")
	call append(line(".")+17,"typedef unsigned long long ull;")
	call append(line(".")+18,"const int sigma_size=26;")
	call append(line(".")+19,"const int N=100+50;")
	call append(line(".")+20,"const int MAXN=100000+50;")
	call append(line(".")+21,"const int inf=0x3fffffff;")
	call append(line(".")+22,"const double eps=1e-8;")
	call append(line(".")+23,"const int HASH=100007;")
	call append(line(".")+24,"const int mod=1000000000+7;")
	call append(line(".")+25,"#define L(x) (x<<1)")
	call append(line(".")+26,"#define R(x) (x<<1|1)")
	call append(line(".")+27,"#define Ls(x) (x->ch[0])")
	call append(line(".")+28,"#define Rs(x) (x->ch[1])")
	call append(line(".")+29,"#define PII pair<int, int>")
	call append(line(".")+30,"#define mk(x,y) make_pair((x),(y))")
	call append(line(".")+31,"int main(){")
	call append(line(".")+32,"	return 0;")
	call append(line(".")+33,"}")
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

