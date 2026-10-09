# Baka Team ICPC Notebook

This repository contains the source code for our team's ICPC notebook. 
The notebook is available as a [PDF](output/main.pdf).


## Team member

| Name | Codeforces |
|---|---|
| Bao Quy Dinh Tan (Asamai) | [Asamai](https://codeforces.com/profile/Asamai) |
| Ha Xuan Thien (ShineNoLife) | [Shine_](shine_)  |
| Tran Quang Truong (QioCas) | [Chau](https://codeforces.com/profile/Chau) |


## Requirements

Install a LaTeX distribution that provides `pdflatex` and the relevant packages. 

```bash
sudo apt update
sudo apt install texlive-latex-extra texlive-fonts-recommended python3-pygments
```

### Building the notebook

From the repository root, run:

```bash
bash build.sh
```

The generated document is saved as `output/main.pdf`.