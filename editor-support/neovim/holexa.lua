-- HOLEXA Neovim Support
-- File: ~/.config/nvim/lua/holexa.lua
-- Code like a Dragon. Think like a Human.

-- Register filetype
vim.filetype.add({
    extension = { hlx = "holexa" }
})

-- Setup LSP
local lspconfig = require('lspconfig')
local configs   = require('lspconfig.configs')

if not configs.hlx_lsp then
    configs.hlx_lsp = {
        default_config = {
            cmd = { 'hlx-lsp' },
            filetypes = { 'holexa' },
            root_dir = lspconfig.util.root_pattern('hlxpm.json', '.git'),
            settings = {}
        }
    }
end

lspconfig.hlx_lsp.setup({
    on_attach = function(client, bufnr)
        local opts = { noremap=true, silent=true, buffer=bufnr }
        vim.keymap.set('n', 'gd', vim.lsp.buf.definition, opts)
        vim.keymap.set('n', 'K',  vim.lsp.buf.hover, opts)
        vim.keymap.set('n', '<leader>r', function()
            vim.cmd('terminal hlxc run %')
        end, opts)
        vim.keymap.set('n', '<leader>f', function()
            vim.cmd('!hlxfmt %')
        end, opts)
    end
})

-- Treesitter hint
vim.api.nvim_create_autocmd({'BufRead','BufNewFile'}, {
    pattern = '*.hlx',
    callback = function()
        vim.bo.tabstop     = 4
        vim.bo.shiftwidth  = 4
        vim.bo.expandtab   = true
        vim.bo.commentstring = '// %s'
    end
})

print("HOLEXA Neovim support loaded!")
