Sheru is a simple Unix shell clone, built as a learning project. It replicates basic shell behavior, handles multiple commands and redirections, and supports a few essential built-in commands.
Features

    Executes commands with arguments and redirections

    Supports piping and environment variables

    Built-in commands:

        cd — change directory

        pwd — print current directory

        echo — supports only -n flag

        exit — exit the shell

        env — print environment variables

        export — set or append to environment variables (VAR=..., VAR+=..., or print sorted list)

Setup

    Clone the repository:

git clone https://github.com/asynthmorpheonx/minishell.git
cd minishell

Build the executable:

    make

    This will generate the minishell binary.

Usage

Start the shell by running:

./Sheru

Once running, you can type commands just like in a standard shell. Use built-ins like cd or export, or run external programs if they’re in your PATH.
Notes

    The Sheru handles Ctrl+C and Ctrl+\ signals gracefully.

    Environment is inherited from the parent, unless started with env -i.

    Redirection and piping work with combinations of built-ins and external commands.
