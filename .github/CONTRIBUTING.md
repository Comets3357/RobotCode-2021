# Contributing Guidelines

This guide will explain all the steps you need to take in order to commit changes on [2021-RobotCode](https://github.com/Comets3357/2021-RobotCode). It includes how to create issues, add labels and assign members to them, creating branches, and making commits. If you have any questions about contributing to the repository, get in touch with another programmer. 

### Prerequisites
Make sure you have the following tools setup before you get started.
- [WPILib 2021.2.2](https://wpilib.org/)
- [GitKraken](https://www.gitkraken.com/)

## 🎉 Starting with an issue 

Before implmenting new features and changes, make sure you [submit an issue](https://github.com/Comets3357/2021-RobotCode/issues/new/choose). This allows the rest of the team to track the progress of the change.
- `✨ Feature request` - Use this template if you're planning on implementing a new feature.
- `🐛 Bug report` - Use this template if you need to report a bug within the current robot code.

## 🏷️ Adding labels

After you've submitted an issue with all of the information required, add the appropriate labels to your issue. To start off, add a type label that defines what your issue is (e.g. `Type: Feature`). Then, add a priority level label (e.g. `Priority: Medium`). Finally, finish off with a status label (e.g. `Status: Review Needed`). 

### Tracking progress
As you work on your issue, you'll have to make sure you continue to update the labels. For example, if you're feature request gets approved, remove the `Status: Review Needed` label and add the `Status: Confirmed` label. Then when you begin to work on it, change it to `Status: In progress`. By constantly updating the labels, the rest of the team will easily be able to track who's working on what and the progress of each issue. 

### List of labels
Here's a table of all the available labels in the repository and when to use them.
<table>
<thead>
  <tr>
    <th>Category</th>
    <th>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Name&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</th>
    <th>Description</th>
  </tr>
</thead>
<tbody>
    <tr>
    <td rowspan=4>Type</td>
    <td><a href="https://github.com/Comets3357/2021-RobotCode/issues?q=label%3A%22Type%3A+Feature%22+"><img src="https://img.shields.io/badge/-Feature-ff78cb?style=flat-square" alt="Feature"></a></td>
    <td>A feature request for the robot that has not already been added.</td>
  </tr>
  <tr>
    <td><a href="https://github.com/Comets3357/2021-RobotCode/issues?q=label%3A%22Type%3A+Enhancement%22+"><img src="https://img.shields.io/badge/-Enhancement-00cded?style=flat-square" alt="Enhancement"></a></td>
    <td>An enhancement request for an existing feature on the robot. </td>
  </tr>
  <tr>
    <td><a href="https://github.com/Comets3357/2021-RobotCode/issues?q=label%3A%22Type%3A+Idea%22+"><img src="https://img.shields.io/badge/-Idea-c377e0?style=flat-square" alt="Idea"></a></td>
    <td>An idea request for the robot that is not needed for the main functionality but could be useful.</td>
  </tr>
  <tr>
    <td><a href="https://github.com/Comets3357/2021-RobotCode/issues?q=label%3A%22Type%3A+Bug%22+"><img src="https://img.shields.io/badge/-Bug-ff3d41?style=flat-square" alt="Bug"></a></td>
    <td>A bug report that will require a hotfix or bugfix depending on its priority.</td>
  </tr>
  <tr>
    <td rowspan=4>Priority</td>
    <td><a href="https://github.com/Comets3357/2021-RobotCode/issues?q=label%3A%22Priority%3A+Low%22+"><img src="https://img.shields.io/badge/-Low-fcd000?style=flat-square" alt="Low"></a></td>
    <td>Changes that aren't necessary for the robot or are just possible ideas.</td>
  </tr>
  <tr>
    <td><a href="https://github.com/Comets3357/2021-RobotCode/issues?q=label%3A%22Priority%3A+Medium%22+"><img src="https://img.shields.io/badge/-Medium-f8931f?style=flat-square" alt="Medium"></a></td>
    <td>Changes that are required but have potential alternatives or don't need to be completed right away.</td>
  </tr>
  <tr>
    <td><a href="https://github.com/Comets3357/2021-RobotCode/issues?q=label%3A%22Priority%3A+High%22+"><img src="https://img.shields.io/badge/-High-ff3d41?style=flat-square" alt="High"></a></td>
    <td>Changes which are important towards the robots functionality and should be worked on before any of the medium and low priorities.</td>
  </tr>
  <tr>
    <td><a href="https://github.com/Comets3357/2021-RobotCode/issues?q=label%3A%22Priority%3A+Critical%22+"><img src="https://img.shields.io/badge/-Critical-e80033?style=flat-square" alt="Critical"></a></td>
    <td>Emergency fixes that need attention ASAP. Only use this for critical bugs found in the main branch.</td>
  </tr>
  <tr>
    <td rowspan=6>Status</td>
    <td><a href="https://github.com/Comets3357/2021-RobotCode/issues?q=label%3A%22Status%3A+Review+needed%22+"><img src="https://img.shields.io/badge/-Review%20needed-fcd000?style=flat-square" alt="Review needed"></a></td>
    <td>Awaiting on approval for the suggested feature or change.</td>
  </tr>
  <tr>
    <td><a href="https://github.com/Comets3357/2021-RobotCode/issues?q=label%3A%22Status%3A+Denied%22+"><img src="https://img.shields.io/badge/-Denied-ff3d41?style=flat-square" alt="Denied"></a></td>
    <td>Issue has been denied and will be closed. </td>
  </tr>
  <tr>
    <td><a href="https://github.com/Comets3357/2021-RobotCode/issues?q=label%3A%22Status%3A+Confirmed%22+"><img src="https://img.shields.io/badge/-Confirmed-7bd938?style=flat-square" alt="Confirmed"></a></td>
    <td>Issue has been approved and will be worked on.</td>
  </tr>
  <tr>
    <td><a href="https://github.com/Comets3357/2021-RobotCode/issues?q=label%3A%22Status%3A+In+progress%22+"><img src="https://img.shields.io/badge/-In%20progress-fcd000?style=flat-square" alt="In progress"></a></td>
    <td>Issue is being worked on. </td>
  </tr>
  <tr>
    <td><a href="https://github.com/Comets3357/2021-RobotCode/issues?q=label%3A%22Status%3A+On+hold%22+"><img src="https://img.shields.io/badge/-On%20hold-f8931f?style=flat-square" alt="On hold"></a></td>
    <td>Issue won't be worked on temporarily.</td>
  </tr>
  <tr>
    <td><a href="https://github.com/Comets3357/2021-RobotCode/issues?q=label%3A%22Status%3A+Complete%22+"><img src="https://img.shields.io/badge/-Complete-7bd938?style=flat-square" alt="Complete"></a></td>
    <td>Issue has been completed and can be closed if no further work will be done on it.</td>
  </tr>
</tbody>
</table>

## 👷 Assigning members 

If you'll be the one working on the issue you submitted, make sure you assign youself to it. If you're working on it with other team members, make sure you assign them to it aswell. You can do this by selecting the settings icon next to `Assignees` and selecting the users who'll be working on the issue. 

## 🌱 Creating a new branch

The main organization of this repository follows a system called [Gitflow](https://support.gitkraken.com/git-workflows-and-extensions/git-flow/). Using this system is made very simple with GitKraken. They have an integrated Gitflow interface which allows you to easily create the appropriate branches.

### Types of branches
Gitflow utilizes 5 types of branches: main, develop, feature, release, and hotfix.
- `main` - This branch hosts all of the production ready releases of the code.
- `develop` - All new features will be pushed to this branch so they can be accumlated and then pushed into the `main` branch as a release.
- `feature` - Create a feature branch for any code change and publish it to the `develop` branch when complete. 
- `release` - When the `develop` branch is ready to be pushed to the `main` branch, use this branch to merge the two. 
- `hotfix` - If an uncaught bug is found in the `main` branch, use this branch to fix the code and publish back to the main branch. 

Here's a diagram of an example Gitflow setup. (Image courtsey of [GitKraken](https://www.gitkraken.com/learn/git/git-flow))
<a href="https://www.gitkraken.com/learn/git/git-flow"><img src="https://www.gitkraken.com/img/landing-page/git-flow-4.svg" width="50%" alt="diagram"></a>

### Initializing Gitflow
To access the Gitflow interface in GitKraken, you'll first need to intialize Gitflow. 
1. Open the repository in GitKraken. 
2. Go to preferences by clicking the settings icon in the top right corner.
3. Select Gitflow near the bottom of the left side bar.
4. Change `master` to `main`. 
5. Click the green 'Initialize Gitflow button.
6. Exit out of preferences.

>It's important that you change `master` to `main` because by default, the origin of the repository is the `main` branch in GitHub. It used to be `master` which is why GitKraken uses it but GitHub recently updated it to `main`. If you forget to do this, it will create another branch in the repository called `master` which is not what we want.

Now that you've initalized Gitflow, you should see a `GITFLOW` section in the left side bar of the repository. Hover over the text `GITFLOW` and click the green button. That should pull out a side bar with 6 buttons. That is the Gitflow interface. 

### Using Gitflow
- Select & naming a branch
  - To create a branch, select either `Feature`, `Release`, or `Hotfix`. Descriptions for each are listed above in this section.
  - After clicking the approriate button, type in the name for the branch according to the issue you're working on. For example if the issue is feature called [Drivebase](https://github.com/Comets3357/202-RobotCode/issues/1), then just name it `Drivebase`. Also, make sure you keep the prefix (e.g.`feature/`) in the name. 
- Choose the location of the branch
  - Before you click `Start Feature`, make sure you're creating the branch from the right location. If you're adding a new feature, you'll most likely just use `Latest develop`.
  - If you need to create the branch from another location, then exit out of the Gitflow interface, open the correct branch location you want to start it from, and then go back to the Gitflow interface and select `Current Branch`. That will create the branch from whatever branch you currently have open in GitKraken. 
- Create the branch
  - Double check that you're making the branch as you would like it to be. 
  - When you're ready, go ahead and click the green start button. Your branch will then be created.

## 🛠️ Committing changes

There's just one more step now: committing your changes. Whether you're ready to push finalized code for your feature or you're just sharing what you've done so far with a team member, you'll need to commit your changes. This section will explain all of the steps so you do it properly.

### Staging files
When you open the repository in GitKraken after you've made changes, you should notice that there's a side bar on the right that says "file changes on *branch name*". Underneath should show a list of unstaged files which you've either added, removed, or edited in the repository, and below that is an empty container for unstaged files. Whichever files you stage will be the ones that are included in your commit. Most of the time, you'll be committing all the files you've edited so you can go ahead and click the green button that says "Stage all changes". If not, you can select individual files by hovering over their names and clicking the green "stage file" button.

### Writing the commit message
There are two inputs for the commit message: the summary and description. The description is fairly simple. Just explain what your changes will do for the bot. This part is totally open ended so don't worry. On the other hand, the commit summary is a bit complex. Follow these steps to do it correctly. 
- Find the descriptor from the naming conventions that matches your changes.
  - All the descriptors are in the list below. For example, if you're adding a new feature, you'll be using "Add". If you're not sure which to pick, ask another programmer. 
- Copy and paste the appropriate descriptor and its emoji into the summary input on GitKraken.
  - Make sure you add a space between the emoji and the descriptor 
- Write the name for your commit
  - Following the descriptor, add in the name of your commit. Like the example in the creating a branch section, if you're working on the [Drivebase](https://github.com/Comets3357/2020-RobotCode/issues/1), then just type "drive subsystem" as you'll be adding code for the drive subsystem. 
- Add the issue number in paranthesis
  - Which ever issue you're working on will be assigned a number by GitHub. All the issues have numbers in chronological order based on when it was created. 
  - As an example, if you're working on [Drivebase](https://github.com/Comets3357/2020-RobotCode/issues/1), then you'd add "(#1)" after the name of the commit. 
In the end, you're commit summary should include the emoji, descriptor, name, and issue number. So the final commit summary for the [Drivebase](https://github.com/Comets3357/2020-RobotCode/issues/1) should look like "[✨ Add drive subsystem (#1)](https://github.com/Comets3357/2020-RobotCode/commit/d283cd413ba0c31ab71f413ec0b164131a115d8e)" 

### Naming Conventions
<table>
  <thead>
    <tr>
        <td>Descriptor</td>
        <td>Emoji</td>
        <td>Description</td>
    </tr>
    </thead>
  <tbody>
    <tr>
        <td rowspan=4>Add</td>
        <th>✨</th>
        <td>Add new functional code</td>
    </tr>
    <tr>
        <th>🚧</th>
        <td>Add new unfinished/unfunctional code</td>
    </tr>
    <tr>
        <th>💬</th>
        <td>Add comments</td>
    </tr>
    <tr>
      <th>⚗</th>
      <td>Add experimental code</td>
    </tr>
    <tr>
        <td rowspan=2>Remove</td>
        <th>🔥</th>
        <td>Remove code files</td>
    </tr>
    <tr>
        <th>✂️</th>
        <td>Remove code snippets</td>
    </tr>
    <tr>
        <td rowspan=6>Update</td>
        <th>🔨</th>
        <td>Update code</td>
    </tr>
    <tr>
        <th>📝</th>
        <td>Update documentation</td>
    </tr>
    <tr>
        <th>📦</th>
        <td>Update compiled files packages</td>
    </tr>
    <tr>
        <th>⬆️</th>
        <td>Upgrade dependencies</td>
    </tr>
    <tr>
        <th>⬇️</th>
        <td>Downgrade dependencies</td>
    </tr>
    <tr>
        <th>👷</th>
        <td>Update CI</td>
    </tr>
    <tr>
        <td rowspan=2>Fix</td>
        <th>🐛</th>
        <td>Fix a bug with a bugfix</td>
    </tr>
    <tr>
        <th>🚑</th>
      <td>Fix a critical bug with a hotfix</td>
    </tr>
    <tr>
        <td rowspan=4>Refactor</td>
        <th>♻️</th>
        <td>Refactor multiple things</td>
    </tr>
    <tr>
        <th>🚚</th>
        <td>Refactor files by moving or renaming</td>
    </tr>
    <tr>
        <th>✏️</th>
        <td>Refactor files by editing code</td>
    </tr>
    <tr>
        <th>🏗</th>
        <td>Refactor architecure</td>
    </tr>
    <tr>
        <td>Release</td>
        <th>🚀</th>
        <td>Release the code in the development branch to the main branch</td>
    </tr>
  </tbody>
</table>

### Committing the changes
After you've created your commit message, you're ready to commit your changes. Click the green "commit changes" button and give yourself a pat on the back. You've now successfully made a commit. All you have to do now is push your commit to GitHub using the push icon in GitKraken. 

## 🏅 Conclusion
Congratulations! After completeing all the steps above, you will have succesfully and properly contirbuted to the repository. There truly is a lot to do but once you get the hang of it, it'll be much easier. By having an organized contributing system, not only the programmers, but the rest of the team will easily be able to understand exactly what we're working on. Thanks for taking the time to read through this and good luck with your future contributions!
