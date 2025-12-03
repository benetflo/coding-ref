# Guide

- Make a binary folder if it does not already exist:
```
mkdir -p ~/bin
```
- Add to PATH and reload configuration:
```
echo 'export PATH="$HOME/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
```
- Move script to ~/bin/ and make it executable:
```
mv test_script ~/bin/
chmod +x ~/bin/test_script
```

