---
tags:
    - aws
    - dev
    - post
created: 2024-05-14
---

# Set up AWS credentials
First, make sure you have the [CLI](https://aws.amazon.com/cli/) installed (on Ubuntu `sudo snap install aws-cli --classic`).

Second, [get a set of credentials](https://docs.aws.amazon.com/singlesignon/latest/userguide/howtogetcredentials.html).

Then run `aws configure` and answer the prompts:

```
aws configure
AWS Access Key ID: ****************AAAA
AWS Secret Access Key? ****************BBBB
Default region name [us-west-2]:
Default output format [None]:
```
