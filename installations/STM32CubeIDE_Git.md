# Prerequisites
* STM32CUBEIDE
* GitHub Account

**VERSIONS USED IN THIS GUIDE**
- STM32CubeIDE v1.19.0
- EGit v7.4.0

# Setup steps:

### Create a personal access token in GitHub
* Go to **Settings** -> **Developer Settings** -> **Personal access tokens** -> **Tokens (classic)** -> **Generate new token (classic)**.
* Provide details for the token by writing a note to describe its purpose and selecting an expiration time. Choose the scopes (permissions) you wish to provide access to, as scopes determine what actions the token can perform.
* Click **Generate token**.
* The token is only displayed once, so make sure to copy it and store it somewhere secure.

### Install the EGit plugin
*  Launch STM32CubeIDE -> Help -> Eclipse Marketplace.
*  In the search bar, search for 'EGit' and click **Install**. Follow the prompts to complete the installation.
*  Restart STM32CubeIDE.
*  Go to: **Window** -> **Show View** -> **Other**.
*  In the dialog that appears, expand the **Git** folder, select **Git Repositories** and click **OPEN**.
*  Choose one of the following available options:
```
Add an existing local Git repository to this view
Clone a Git repository and add the clone to this view
Create new Git repository and add it to this view
```
### Clone a GitHub repository
* Choose the option "Clone a Git repository and add the clone to this view".
* In the window that appears, paste the URL of the repository you want to clone.
* In the "Authentication" field, enter your GitHub username. Use the personal access token you generated earlier instead of your GitHub password.
* Click "Next" and configure the last settings.

### Share the project
* Right-click on the project in the Project Explorer.
* Navigate to the "Team" menu and click on **Share project**.
* Enter your GitHub username and the personal token in the dialog that appears.
* Choose the repository you cloned earlier.
* Click **Finish**.

### Commit changes
* Right-click on the project in the Project Explorer.
* Navigate to the "Team" menu and click on **Commit** to open the Git-staging window.
* Move unstaged changes into staged changes by pressing the double '+' button or by dragging and dropping files.
* Enter a commit message in the commit message field.
* Click the "Commit and Push" button to commit and push to the remote repository.
* Follow any additional prompts to complte the push process.
* Go to the repo in your web browser to verify the changes.

