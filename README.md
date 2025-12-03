# 42sh - Advanced Shell

An implementation of a UNIX shell with advanced features.

## Features

- Command execution and piping
- Input/output redirection
- Environment variable management
- History with navigation
- And many more...

## ChatGPT Integration

This shell integrates with the OpenAI ChatGPT API. Type your query and press `Ctrl+I` to send it to ChatGPT and receive the response directly in your terminal.

## Building

### Dependencies

Before building, you'll need to install the required dependencies:

This will install the necessary libraries (libcurl and libjson-c).

### Compilation

To build the shell:

```bash
make
```

### Running

```bash
./42sh
```

## Environment Variables Configuration

The shell supports secure environment variable configuration through a `.env` file for storing sensitive API keys.

### Setup

1. Copy the example file to create your own environment file:
   ```bash
   cp .env.example .env
   ```

2. Edit the `.env` file with your actual API keys:
   ```bash
   nano .env
   ```

3. Add your OpenAI API key:
   ```
   OPENAI_API_KEY=your_actual_api_key_here
   ```

The `.env` file is automatically ignored by Git to prevent accidentally committing sensitive information.

### Security Best Practices

- Never commit your `.env` file to version control
- Restrict the file permissions: `chmod 600 .env`
- Don't share your API keys with others
- Rotate your API keys periodically for enhanced security

## Using the ChatGPT Feature

1. Type your query in the shell prompt
2. Press `Ctrl+I` to send it to ChatGPT
3. The response will be displayed in the terminal


Credit to Louis BAGNOL, Gabriel BRUMENT, Louis PUJOL, Gabin SCHIRO
