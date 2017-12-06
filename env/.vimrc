
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Install Vundle from
" https://github.com/VundleVim/Vundle.vim
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

colorscheme desert

syntax on

set shiftwidth=4
set expandtab
set cindent
set autoindent
set showmatch
set ruler               " Show the line and column numbers of the cursor.
set showmode            " Show current mode.
set hlsearch            " Highlight search matches.
set noerrorbells        " No beeps.
set tabstop=4           " Number of spaces <tab> counts for.
set textwidth=0         " Don't wrap words by default.

set guifont=Neep\ 20

" set columns=80


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" CSCOPE settings for vim           
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"
" This file contains some boilerplate settings for vim's cscope interface,
" plus some keyboard mappings that I've found useful.
"
" USAGE: 
" -- vim 6:     Stick this file in your ~/.vim/plugin directory (or in a
"               'plugin' directory in some other directory that is in your
"               'runtimepath'.
"
" -- vim 5:     Stick this file somewhere and 'source cscope.vim' it from
"               your ~/.vimrc file (or cut and paste it into your .vimrc).
"
" NOTE: 
" These key maps use multiple keystrokes (2 or 3 keys).  If you find that vim
" keeps timing you out before you can complete them, try changing your timeout
" settings, as explained below.
"
" Happy cscoping,
"
" Jason Duell       jduell@alumni.princeton.edu     2002/3/7
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


" This tests to see if vim was configured with the '--enable-cscope' option
" when it was compiled.  If it wasn't, time to recompile vim... 
if has("cscope")

    """"""""""""" Standard cscope/vim boilerplate

    " use both cscope and ctag for 'ctrl-]', ':ta', and 'vim -t'
    set cscopetag

    " check cscope for definition of a symbol before checking ctags: set to 1
    " if you want the reverse search order.
    set csto=0

    " add any cscope database in current directory
    if filereadable("cscope.out")
        cs add cscope.out  
    " else add the database pointed to by environment variable 
    elseif $CSCOPE_DB != ""
        cs add $CSCOPE_DB
    endif

    " show msg when any other cscope db added
    set cscopeverbose  


    """"""""""""" My cscope/vim key mappings
    "
    " The following maps all invoke one of the following cscope search types:
    "
    "   's'   symbol: find all references to the token under cursor
    "   'g'   global: find global definition(s) of the token under cursor
    "   'c'   calls:  find all calls to the function name under cursor
    "   't'   text:   find all instances of the text under cursor
    "   'e'   egrep:  egrep search for the word under cursor
    "   'f'   file:   open the filename under cursor
    "   'i'   includes: find files that include the filename under cursor
    "   'd'   called: find functions that function under cursor calls
    "
    " Below are three sets of the maps: one set that just jumps to your
    " search result, one that splits the existing vim window horizontally and
    " diplays your search result in the new window, and one that does the same
    " thing, but does a vertical split instead (vim 6 only).
    "
    " I've used CTRL-\ and CTRL-@ as the starting keys for these maps, as it's
    " unlikely that you need their default mappings (CTRL-\'s default use is
    " as part of CTRL-\ CTRL-N typemap, which basically just does the same
    " thing as hitting 'escape': CTRL-@ doesn't seem to have any default use).
    " If you don't like using 'CTRL-@' or CTRL-\, , you can change some or all
    " of these maps to use other keys.  One likely candidate is 'CTRL-_'
    " (which also maps to CTRL-/, which is easier to type).  By default it is
    " used to switch between Hebrew and English keyboard mode.
    "
    " All of the maps involving the <cfile> macro use '^<cfile>$': this is so
    " that searches over '#include <time.h>" return only references to
    " 'time.h', and not 'sys/time.h', etc. (by default cscope will return all
    " files that contain 'time.h' as part of their name).


    " To do the first type of search, hit 'CTRL-\', followed by one of the
    " cscope search types above (s,g,c,t,e,f,i,d).  The result of your cscope
    " search will be displayed in the current window.  You can use CTRL-T to
    " go back to where you were before the search.  
    "

    nmap <C-\>s :cs find s <C-R>=expand("<cword>")<CR><CR>	
    nmap <C-\>g :cs find g <C-R>=expand("<cword>")<CR><CR>	
    nmap <C-\>c :cs find c <C-R>=expand("<cword>")<CR><CR>	
    nmap <C-\>t :cs find t <C-R>=expand("<cword>")<CR><CR>	
    nmap <C-\>e :cs find e <C-R>=expand("<cword>")<CR><CR>	
    nmap <C-\>f :cs find f <C-R>=expand("<cfile>")<CR><CR>	
    nmap <C-\>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
    nmap <C-\>d :cs find d <C-R>=expand("<cword>")<CR><CR>	


    " Using 'CTRL-spacebar' (intepreted as CTRL-@ by vim) then a search type
    " makes the vim window split horizontally, with search result displayed in
    " the new window.
    "
    " (Note: earlier versions of vim may not have the :scs command, but it
    " can be simulated roughly via:
    "    nmap <C-@>s <C-W><C-S> :cs find s <C-R>=expand("<cword>")<CR><CR>	

    nmap <C-@>s :scs find s <C-R>=expand("<cword>")<CR><CR>	
    nmap <C-@>g :scs find g <C-R>=expand("<cword>")<CR><CR>	
    nmap <C-@>c :scs find c <C-R>=expand("<cword>")<CR><CR>	
    nmap <C-@>t :scs find t <C-R>=expand("<cword>")<CR><CR>	
    nmap <C-@>e :scs find e <C-R>=expand("<cword>")<CR><CR>	
    nmap <C-@>f :scs find f <C-R>=expand("<cfile>")<CR><CR>	
    nmap <C-@>i :scs find i ^<C-R>=expand("<cfile>")<CR>$<CR>	
    nmap <C-@>d :scs find d <C-R>=expand("<cword>")<CR><CR>	


    " Hitting CTRL-space *twice* before the search type does a vertical 
    " split instead of a horizontal one (vim 6 and up only)
    "
    " (Note: you may wish to put a 'set splitright' in your .vimrc
    " if you prefer the new window on the right instead of the left

    nmap <C-@><C-@>s :vert scs find s <C-R>=expand("<cword>")<CR><CR>
    nmap <C-@><C-@>g :vert scs find g <C-R>=expand("<cword>")<CR><CR>
    nmap <C-@><C-@>c :vert scs find c <C-R>=expand("<cword>")<CR><CR>
    nmap <C-@><C-@>t :vert scs find t <C-R>=expand("<cword>")<CR><CR>
    nmap <C-@><C-@>e :vert scs find e <C-R>=expand("<cword>")<CR><CR>
    nmap <C-@><C-@>f :vert scs find f <C-R>=expand("<cfile>")<CR><CR>	
    nmap <C-@><C-@>i :vert scs find i ^<C-R>=expand("<cfile>")<CR>$<CR>	
    nmap <C-@><C-@>d :vert scs find d <C-R>=expand("<cword>")<CR><CR>


    """"""""""""" key map timeouts
    "
    " By default Vim will only wait 1 second for each keystroke in a mapping.
    " You may find that too short with the above typemaps.  If so, you should
    " either turn off mapping timeouts via 'notimeout'.
    "
    "set notimeout 
    "
    " Or, you can keep timeouts, by uncommenting the timeoutlen line below,
    " with your own personal favorite value (in milliseconds):
    "
    "set timeoutlen=4000
    "
    " Either way, since mapping timeout settings by default also set the
    " timeouts for multicharacter 'keys codes' (like <F1>), you should also
    " set ttimeout and ttimeoutlen: otherwise, you will experience strange
    " delays as vim waits for a keystroke after you hit ESC (it will be
    " waiting to see if the ESC is actually part of a key code like <F1>).
    "
    "set ttimeout 
    "
    " personally, I find a tenth of a second to work well for key code
    " timeouts. If you experience problems and have a slow terminal or network
    " connection, set it higher.  If you don't set ttimeoutlen, the value for
    " timeoutlent (default: 1000 = 1 second, which is sluggish) is used.
    "
    "set ttimeoutlen=100

endif

"	multiwin.vim:	Show every buffer in its own window and use
"					statuslines as "tabs"
"	Maintainer:		Patrick Avery, patrick dot avery at gmail dot com
"	Created:		Tue 01 Apr 2004 03:35:39 AM CDT
"	Last Modified:	Fri 24 Dec 2004 01:56:21 AM CST
"	Version:		1.4
"	Usage:			place in vimfiles/plugin

if exists("s:loaded") || &cp || &diff || exists("g:singlewin")
	finish
endif
let s:initialized = 0
if exists("g:multiwin_qfh")
	let s:QFHeight = g:multiwin_qfh
else
	let s:QFHeight = 10
endif

" UI Settings: These settings change the behavior of vim to allow the
" script to work.
"____________________________________________________________________
function! s:SetUI()
	set noequalalways
	set splitbelow
	set winheight=1
	set winminheight=0
	set laststatus=2
endfunction

function! s:BackupUI()
	if &equalalways
		let s:ea = "ea"
	else
		let s:ea = "noea"
	endif
	if &sb
		let s:sb = "sb"
	else
		let s:sb = "nosb"
	endif
	let s:wh = &winheight
	let s:wmh = &winminheight
	let s:ls = &laststatus
endfunction

function! s:RestoreUI()
	exec "set " . s:ea
	exec "set " . s:sb
	exec "set winheight=" . s:wh
	exec "set winminheight=" . s:wmh
	exec "set laststatus=" . s:ls
endfunction

" Auto Commands: These autocommands make each window shrink and grow
" effectively without the negative effects of having winheight set too
" high and make VIM always behave as if -o was on the command line.
"_____________________________________________________________________
function! s:AutoCommands()
	augroup MultiWin
		autocmd!
		autocmd VimEnter * nested all | wincmd _
		autocmd WinEnter * nested call <SID>Maximize()
		autocmd BufWinEnter * nested if eventhandler() | sball | wincmd W | endif
	augroup END
endfunction

function! s:RemoveAutoCommands()
	augroup MultiWin
		autocmd!
	augroup END
endfunction

" Mappings: Makes a runtime toggle available to the user
"_____________________________________________________________________
if !hasmapto("<Plug>MultiWinToggle")
	nmap <unique> <silent>	<Leader>win <Plug>MultiWinToggle
endif

noremap	<silent> <script>	<Plug>MultiWinToggle	<SID>Toggle
noremap	<silent>			<SID>Toggle				:call <SID>ToggleMultiWin()<CR>

function! s:ExtraMappings()
	nmap	<silent>		gf						:new <cfile><CR>
	if has("gui")
		nmap	<silent>		<A-Left>				:wincmd k<CR>
		nmap	<silent>		<A-Right>				:wincmd j<CR>
	else
		nmap	<silent>		<C-Left>				:wincmd k<CR>
		nmap	<silent>		<C-Right>				:wincmd j<CR>
	endif	
endfunction

function! s:RemoveExtraMappings()
	unmap gf
	unmap <A-Left>
	unmap <A-Right>
endfunction

" State Functions: these functions initialize, destroy, and toggle
"_____________________________________________________________________
function! s:EnableMultiWin()
	call <SID>BackupUI()
	call <SID>SetUI()
	call <SID>AutoCommands()
	if !exists("g:multiwin_noextra")
		call <SID>ExtraMappings()
	endif
	let s:initialized = 1
endfunction

function! s:DisableMultiWin()
	call <SID>RestoreUI()
	call <SID>RemoveAutoCommands()
	if !exists("g:multiwin_noextra")
		call <SID>RemoveExtraMappings()
	endif
	let s:initialized = 0
endfunction

function! s:ToggleMultiWin()
	if s:initialized
		call <SID>DisableMultiWin()
	else
		call <SID>EnableMultiWin()
	endif
endfunction

function! s:Maximize()
	if (getbufvar(winbufnr(winnr()), "&buftype") == "quickfix")
		exec "resize " . s:QFHeight
	else
		wincmd _
		call <SID>ResizeQF()
	endif
endfunction

function! s:ResizeQF()
	set eventignore=WinEnter
	let i = 1
	let cbuf = winbufnr(i)
	while (cbuf != -1)
		if (getbufvar(cbuf, "&buftype") == "quickfix")
			exec i . "wincmd w"
			exec "resize " . s:QFHeight
			wincmd p
			break
		endif
		let i = i+1
		let cbuf = winbufnr(i)
	endwhile
	set eventignore-=WinEnter
endfunction

" Main:
"_____________________________________________________________________
call <SID>EnableMultiWin()

let s:loaded = 1
" vim:ts=4:fo=roq:
