Install git

https://git-scm.com/install/windows

https://git-scm.com/install/mac


Sign in with your github on your terminal / command line

Replace the boiler plate with your name and the email with the one you used for your github account
```bash
git config --global user.name "Your Name"
git config --global user.email "your_email@example.com"
```

Windows
How to set up
```bash
cd ~\Documents
git clone https://github.com/0Turtlez/Cg-project.git "CG_Project"
cd CG_Project
```

Mac
```bash
cd ~/Documents
git clone https://github.com/0Turtlez/Cg-project.git "CG_Project"
cd CG_Project
```


Windows: Pull changes to github
```bash
cd ~\Documents\CG_Project
git pull
```

Mac: Pull changes to github
```bash
cd ~/Documents/CG_Project
git pull
```

Windows: Push changes to github
```bash
cd ~\Documents\CG_Project
git add .
git commit -m "What you changed"
git push origin main
```

Mac: Push changes to github
```bash
cd ~/Documents/CG_Project
git add .
git commit -m "What you changed"
git push origin main
```