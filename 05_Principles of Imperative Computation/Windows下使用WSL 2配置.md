# Windows下安装WSL 2

## 系统版本要求

必须运行 Windows 10 版本 2004 及更高版本（内部版本 19041 及更高版本）或 Windows 11

> 选择**"Windows 徽标键 + R"，**键入**winver**来查看电脑版本

## 安装

通过在**管理员模式下 **PowerShell 或 Windows 命令提示符中输入以下命令，然后重新启动计算机来安装运行WSL

```powershell
wsl --install
```

此命令将启用所需的可选组件，下载最新的Linux内核，**将WSL 2设置为默认值**，并为您安装Linux发行版（默认情况下为**Ubuntu**）。

首次启动新安装的 Linux 发行版时，将打开一个控制台窗口，系统将要求您等待文件解压缩并存储在您的计算机上。

## 更改发行版

通过在**管理员模式下 **PowerShell 或 Windows 命令提示符中输入以下命令查看可安装的有效分发

```powershell
wsl -l -o
wsl --list --online
```

通过在**管理员模式下 **PowerShell 或 Windows 命令提示符中输入以下命令安装新分发

```powershell
wsl --install -d <Distribution Name>
```

通过在**管理员模式下 **PowerShell 或 Windows 命令提示符中输入以下命令用新分发替换旧分发

```powershell
wsl --install -d <Distribution Name> <Distribution Name>
```

## 查看已安装发行版

通过在**管理员模式下 **PowerShell 或 Windows 命令提示符中输入以下命令查看已安装分发的状态和版本

```powershell
wsl -l -v
```