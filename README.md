# ccalendar
Utility to set reminder of events written in C++!

# How to compile
```
git clone git@github.com:Xaxurro/ccalendar.git
cd ccalendar
make release
```

## OPTIONAL: Move it into your `bin` directory to use it from everywhere
`sudo mv ccalendar /bin`

## OPTIONAL: Add the syntax file into your neovim config
```
mkdir -P ~/.config/nvim/after/syntax
mv syntax.lua ~/.config/nvim/after/syntax/cldr.lua
```
And don't forget to add this to your `init.lua`
```lua
vim.api.nvim_create_autocmd({ 'BufRead', 'BufNewFile' }, {
	pattern = '*.cldr',
	callback = function()
		vim.bo.filetype = 'cldr'
	end,
})
```

# How to use
Check the [wiki](https://github.com/Xaxurro/ccalendar/wiki)
