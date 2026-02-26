-- This file is meant to be used in a neovim config in ~/.config/nvim/after/syntax/cldr.lua
-- make sure to add the following to your init.lua file
--
-- vim.api.nvim_create_autocmd({ 'BufRead', 'BufNewFile' }, {
-- 	pattern = '*.cldr',
-- 	callback = function()
-- 		vim.bo.filetype = 'cldr'
-- 	end,
-- })

if vim.b.cldr_syntax_loaded then
    return
end
vim.b.cldr_syntax_loaded = true

vim.cmd('syntax clear')

local function exec(cmd)
    vim.api.nvim_command(cmd)
end

-- Comments
exec([[syntax match cldrComment +\/\/.*$+]])

-- Description
exec([[syntax match cldrDesc +\S.*+]])

-- Tags
exec([[syntax match cldrTag +\[.\{-}\]+ nextgroup=cldrDesc]])

-- Rules
exec([[syntax match cldrRuleFixed +\<\d\+\>+ contained]])
exec([[syntax match cldrRuleRange +\d\+-\d\++ contained]])
exec([[syntax match cldrRuleWildcard +\*+ contained]])
exec([[syntax match cldrRuleDayOfWeek +#\d+ contained]])
exec([[syntax region cldrRuleList start=+{+ end=+}+ transparent contained contains=cldrRuleFixed,cldrRuleRange,cldrRuleWildcard,cldrRuleDayOfWeek]])

-- Event using nextgroup chain
do
	local separator_null = [[[\ \t.:,;\-_?!\\/|]*]]
	local separator_mandatory = [[[\ \t.:,;\-_?!\\/|]\+]]

	local day_rules = [[\%(\%(\d\{4}\)\?\*\|\d\{1,2}-\d\{1,2}\|\d\{1,2}\|#\d\|{[^}]*}\)]]
	local month_rules = [[\%(\%(\d\{4}\)\?\*\|\d\{1,2}-\d\{1,2}\|\d\{1,2}\|{[^}]*}\)]]
	local year_rules = [[\%(\%(\d\{4}\)\?\*\|\d\{4}-\d\{4}\|\d\{4}\|{[^}]*}\)]]

	exec([[syntax match cldrEventDate +]] .. separator_null .. day_rules .. separator_mandatory .. month_rules .. separator_mandatory .. year_rules .. [[+ nextgroup=cldrTag,cldrDesc contains=cldrRuleFixed,cldrRuleRange,cldrRuleWildcard,cldrRuleList]])
end

-- Fixed Range Event
do
	local day_month = [[\d\{1,2}]]
	local year  = [[\d\{4}]]
	local separator_null = [[[\ \t.:,;\-_?!\\/|]*]]
	local separator_mandatory = [[[\ \t.:,;\-_?!\\/|]\+]]

	local simple_date = day_month .. separator_mandatory .. day_month .. separator_mandatory .. year
	local range_sep = separator_null .. '-' .. separator_null
	local fixed_range = "^" .. separator_null .. simple_date .. range_sep .. simple_date

	exec([[syntax region cldrRangeLine start=/]] .. fixed_range .. [[/ end=/$/ keepend contains=cldrDate,cldrRangeSep,cldrTag,cldrDesc]])
	exec([[syntax match cldrDate +]] .. simple_date .. [[+ contained contains=cldrRuleFixed]])
	exec([[syntax match cldrRangeSep +]] .. range_sep .. [[+ contained]])
end

-- Highlighting Links
exec("highlight link cldrComment      	Comment")
exec("highlight link cldrTag          	Label")
exec("highlight link cldrDesc         	String")
exec("highlight link cldrDate         	Constant")
exec("highlight link cldrEventDate	Number")
exec("highlight link cldrRuleFixed      Number")
exec("highlight link cldrRuleRange    	Number")
exec("highlight link cldrRuleWildcard 	Number")
exec("highlight link cldrRuleDayOfWeek	Number")
exec("highlight link cldrRuleList     	Operator")
exec("highlight link cldrRangeSep     	Operator")

vim.b.current_syntax = "cldr"
