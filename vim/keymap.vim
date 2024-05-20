set nocompatible
let g:mapleader = ";"

filetype plugin on
filetype indent on

nnoremap <Leader>a 0
vnoremap <Leader>a 0
nnoremap <Leader>e $
vnoremap <Leader>e $
nnoremap <Leader>s ^
vnoremap <Leader>s ^
vnoremap <Leader>y "+y
nnoremap <Leader>p "+p
nnoremap <Leader>qq :q<CR>
nnoremap <Leader>qa :qa<CR>
nnoremap <leader>qb :bp\|bd#<CR>
nnoremap <Leader>ww :w<CR>
nnoremap <Leader>wq :wa<CR>:q<CR>
nnoremap <Leader>Q :qa!<CR>
nnoremap <Leader>1 :1b<CR>
nnoremap <Leader>2 :2b<CR>
nnoremap <Leader>3 :3b<CR>
nnoremap <Leader>4 :4b<CR>
nnoremap <Leader>5 :5b<CR>
nnoremap <Leader>6 :6b<CR>
nnoremap <Leader>7 :7b<CR>
nnoremap <Leader>8 :8b<CR>
nnoremap <Leader>9 :9b<CR>
nnoremap <Leader>0 :10b<CR>
nnoremap <leader>w <C-W>
nnoremap <space>w <C-W>
noremap <M-u> <C-w>p<C-u><C-w>p
noremap <M-d> <C-w>p<C-d><C-w>p
nnoremap <space>p :bp<CR>
nnoremap <space>n :bn<CR>

" cargo
nnoremap <space>rr :!cargo run<CR>
nnoremap <space>rj :!cargo check<CR>
nnoremap <space>rg :!cargo build<CR>
nnoremap <space>rf :!cargo fix<CR>
nnoremap <space>rt :!cargo test<CR>
nnoremap <space>gh :nohlsearch<CR>

" nnoremap <space>gg gg=G``<CR>
" inoremap jj <Esc>
" nnoremap <CR> o<Esc>
" inoremap ( ()<esc>i
" inoremap [ []<esc>i
" inoremap " ""<esc>i
" inoremap { {<CR>}<esc>O
nnoremap <Leader>mm m1gUiw`1
inoremap <C-h> <ESC>gUiwgi
inoremap <S-Insert><ESC>:setl paste<CR>gi<C-R>+<ESC>:setl nopaste<CR>gi
inoremap <F11><ESC>:setl paste<CR>gi<C-R>+<ESC>:setl nopaste<CR>gi
set switchbuf=useopen,usetab,newtab
set formatoptions=c,q,r,t
map j gj
map k gk

filetype on
syntax on
" set clipboard=unnamed
set clipboard=unnamedplus
set hidden
set nowrap
set linebreak
set scrolloff=7
set laststatus=2
set cursorline
set textwidth=80
" set cursorcolumn
set colorcolumn=80
set number
" set relativenumber
set ruler
set conceallevel=0
set ignorecase
set hlsearch
set incsearch
set copyindent
"autocmd insertenter * se nocul
set sw=4
set ts=4
" set noet
set et
set ttm=100
" set list
set smartcase
set smarttab
set smartindent
set autoindent
set wildmenu
set backspace=indent,eol,start
" setlocal spell spelllang=en_us,cjk

" indent, syntax
set foldmethod=syntax
" 启动 vim 时关闭折叠代码
set nofoldenable

" 中文乱码
let &termencoding=&encoding
set fileencodings=utf-8,gbk

" 保留光标位置
if has("autocmd")
    au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
endif

" mksession
" nnoremap <leader>ms :execute 'tabdo NERDTreeClose'<CR>:execute 'mksession! .last.vim'<CR>:execute 'wviminfo! .last.viminfo'<CR>
" nnoremap <leader>mr :silent execute 'source .last.vim'<CR>:silent execute 'rviminfo .last.viminfo'<CR>
nnoremap <leader>ms :execute 'mksession! .last.vim'<CR>:execute 'wviminfo! .last.viminfo'<CR>
nnoremap <leader>mr :silent execute 'source .last.vim'<CR>:silent execute 'rviminfo .last.viminfo'<CR>
" nnoremap <space>ls :silent execute 'source .last.vim'<CR>:silent execute 'rviminfo .last.viminfo'<CR>:execute 'tabdo NERDTreeToggle'<CR>:<space>l<CR>

" let showmarks_enable = 1
" let showmarks_include = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
" " Ignore help, quickfix, non-modifiable buffers
" let showmarks_ignore_type = "hqm"
" let showmarks_hlline_lower = 1
" let showmarks_hlline_upper = 1
" hi ShowMarksHLl ctermbg=Yellow   ctermfg=Black  guibg=#FFDB72    guifg=Black
" hi ShowMarksHLu ctermbg=Magenta  ctermfg=Black  guibg=#FFB3FF    guifg=Black

" ctags
set tags=./.tags;,.tags
map <F5> :!ctags -R --c++-kinds=+px --fields=+niazs --extras=+q -f .tags<CR>
imap <F5> :!ctags -R --c++-kinds=+px --fields=+niazs --extras=+q -f .tags<CR>

" clang
" map <F6> :!clang++ -O2 -std=c++14 -stdlib=libc++ -Weverything
map <F6> :!clang++ -O2 -std=c++14  -Weverything
imap <F6> :!clang++ -O2 -std=c++14  -Weverything

" Alt map
function! Terminal_MetaMode(mode)
    set ttimeout
    if $TMUX != ''
        set ttimeoutlen=30
    elseif &ttimeoutlen > 80 || &ttimeoutlen <= 0
        set ttimeoutlen=80
    endif
    if has('nvim') || has('gui_running')
        return
    endif
    function! s:metacode(mode, key)
        if a:mode == 0
            exec "set <M-".a:key.">=\e".a:key
        else
            exec "set <M-".a:key.">=\e]{0}".a:key."~"
        endif
    endfunc
    for i in range(10)
        call s:metacode(a:mode, nr2char(char2nr('0') + i))
    endfor
    for i in range(26)
        call s:metacode(a:mode, nr2char(char2nr('a') + i))
        call s:metacode(a:mode, nr2char(char2nr('A') + i))
    endfor
    if a:mode != 0
        for c in [',', '.', '/', ';', '[', ']', '{', '}']
            call s:metacode(a:mode, c)
        endfor
        for c in ['?', ':', '-', '_']
            call s:metacode(a:mode, c)
        endfor
    else
        for c in [',', '.', '/', ';', '{', '}']
            call s:metacode(a:mode, c)
        endfor
        for c in ['?', ':', '-', '_']
            call s:metacode(a:mode, c)
        endfor
    endif
endfunc

call Terminal_MetaMode(0)

" 精准替换
" confirm：是否替换前逐一确认
" wholeword：是否整词匹配
" replace：被替换字符串
"function! Replace(confirm, wholeword, replace)
"    wa
"    let flag = ''
"    if a:confirm
"        let flag .= 'gec'
"    else
"        let flag .= 'ge'
"    endif
"    let search = ''
"    if a:wholeword
"        let search .= '\<' . escape(expand('<cword>'), '/\.*$^~[') . '\>'
"    else
"        let search .= expand('<cword>')
"    endif
"    let replace = escape(a:replace, '/\&~')
"    execute 'argdo %s/' . search . '/' . replace . '/' . flag . '| update'
"endfunction
"" 不确认、非整词
"nnoremap <Leader>R :call Replace(0, 0, input('Replace '.expand('<cword>').' with: '))<CR>
"" 不确认、整词
"nnoremap <Leader>rw :call Replace(0, 1, input('Replace '.expand('<cword>').' with: '))<CR>
"" 确认、非整词
"nnoremap <Leader>rc :call Replace(1, 0, input('Replace '.expand('<cword>').' with: '))<CR>
"" 确认、整词
"nnoremap <Leader>rcw :call Replace(1, 1, input('Replace '.expand('<cword>').' with: '))<CR>
"nnoremap <Leader>rwc :call Replace(1, 1, input('Replace '.expand('<cword>').' with: '))<CR>

