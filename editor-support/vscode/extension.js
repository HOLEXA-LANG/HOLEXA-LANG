const vscode = require('vscode');
const { exec } = require('child_process');
const path = require('path');

function activate(context) {
    console.log('HOLEXA extension activated!');

    // Run command
    let runCmd = vscode.commands.registerCommand('holexa.run', function() {
        const editor = vscode.window.activeTextEditor;
        if (!editor) return;
        const file = editor.document.fileName;
        const terminal = vscode.window.createTerminal('HOLEXA');
        terminal.show();
        terminal.sendText(`hlxc run "${file}"`);
    });

    // Build command
    let buildCmd = vscode.commands.registerCommand('holexa.build', function() {
        const editor = vscode.window.activeTextEditor;
        if (!editor) return;
        const file = editor.document.fileName;
        const terminal = vscode.window.createTerminal('HOLEXA Build');
        terminal.show();
        terminal.sendText(`hlxc build "${file}"`);
    });

    // Format command
    let fmtCmd = vscode.commands.registerCommand('holexa.format', function() {
        const editor = vscode.window.activeTextEditor;
        if (!editor) return;
        const file = editor.document.fileName;
        exec(`hlxfmt "${file}"`, (err, stdout, stderr) => {
            if (err) {
                vscode.window.showErrorMessage('HOLEXA format failed: ' + stderr);
            } else {
                vscode.window.showInformationMessage('HOLEXA: File formatted!');
            }
        });
    });

    // Format on save
    let saveWatcher = vscode.workspace.onDidSaveTextDocument((doc) => {
        const config = vscode.workspace.getConfiguration('holexa');
        if (doc.languageId === 'holexa' && config.get('formatOnSave')) {
            exec(`hlxfmt "${doc.fileName}"`);
        }
    });

    // Status bar item
    const statusBar = vscode.window.createStatusBarItem(
        vscode.StatusBarAlignment.Left, 100
    );
    statusBar.text = '🐉 HOLEXA';
    statusBar.tooltip = 'HOLEXA Language v1.0.0';
    statusBar.command = 'holexa.run';
    statusBar.show();

    context.subscriptions.push(runCmd, buildCmd, fmtCmd, saveWatcher, statusBar);
}

function deactivate() {}

module.exports = { activate, deactivate };
