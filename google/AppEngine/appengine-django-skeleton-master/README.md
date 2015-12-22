## Python Django Skeleton for Google App Engine

A skeleton for building Python applications on Google App Engine with the
[Django Web Framework](https://www.djangoproject.com/) using
[Cloud SQL](https://cloud.google.com/sql/docs/introduction).

See our other [Google Cloud Platform github
repos](https://github.com/GoogleCloudPlatform) for sample applications and
scaffolding for other python frameworks and use cases.

Note that this project no longer uses the the SDK-provided Django 1.5 library but
uses `pip -t` to vendor Django 1.8 into the lib/ folder.

This project is based on the introductory [Django Tutorial](https://docs.djangoproject.com/en/1.8/intro/tutorial01/)
polls applications.

## Project Creation

The basic skeleton of this project was created using the standard Django commands:

  *  Use the standard Django command to start the project
   ```
   django-admin startproject mysite
   ```
  * Edit the DATABASE field in mysite/settings.py to use the CloudSQL instance locally,
    and use the Unix socket to talk to the same CloudSQL instance through a Unix socket
    when deployed
  * Create appengine_config.py to ensure that libraries vendored into lib/ are on Python's
    sys.path when run.
  * Create [app.yaml](https://cloud.google.com/appengine/docs/python/config/appconfig?hl=en)
    and setup a static file handler in the same folder htat mysite/settings.py is configured
    to collect static files. All other routes are directed to Django's WSGI handler.

## Enable Cloud SQL

This project assumes you are using [CloudSQL](https://cloud.google.com/sql/docs/introduction)
as your database. CloudSQL is a managed MySQL instance hosted by Google Cloud, although you
could also host a MySQL instance elsewhere and use that. Please see instructions below
for how to enable create a CloudSQL instance.

For better scalability, consider
[Cloud Datastore](https://cloud.google.com/datastore/docs/concepts/overview?hl=en), although
you must use a custom backend such as [Djangae](https://github.com/potatolondon/djangae) for your
models to work with it.

## Run Locally
1. Install the [App Engine Python SDK](https://developers.google.com/appengine/downloads).
See the README file for directions. You'll need python 2.7 and [pip 7.0 or later](http://www.pip-installer.org/en/latest/installing.html) installed too.

1. Clone this repo

   ```
   git clone https://github.com/GoogleCloudPlatform/appengine-django-skeleton.git
   ```
1. Install dependencies in the project's `lib/` directory.
   Note: App Engine can only import libraries from inside your project directory. The pip -t flag installs dependencies into the
   directory specified, so here it's used to install the lastest Django version into lib/. appengine_config.py uses the
   appengine vendor extension to ensure lib/ is on the Python sys.path.

   ```
   cd appengine-try-python-django
   pip install -r requirements.txt -t lib
   ```
1. Create a new CloudSQL instance.
    * From the Google Cloud Console, go to [Storage > CloudSQL> Create Instance](https://console.developers.google.com/project/_/sql/create)
    * Under [Access Control > IP Address](https://console.developers.google.com/project/_/sql/instances/polls/access-control/ip),  Request IPv4 Address. This address will be your HOST for remote access to the
      CloudSQL instance in mysite/settings.py, so replace `<your-database-host>` with this address.
    * Under [Databases](https://console.developers.google.com/project/_/sql/instances/polls/databases), click New Database and create the name for your database in mysite/settings.py. Replace
      `<your-database-name>` with this value.

    At this point, your deployed AppEngine application can access the database, after you replace `<your-project-id>` and
    `<your-database-name>` in mysite/settings.py. The following instructions are to connect to the same CloudSQL instance
    locally. Alternatively, you could install a local MySQL instance and use that in development.

    * Under [Access Control > Authorization](https://console.developers.google.com/project/_/sql/instances/polls/access-control/authorization) Under "Allowed Networks", click "Add item", and add Network 0.0.0.0/0. This opens up
          access to your CloudSQL instance from any network. Stricter firewall settings should be considered for production
          applications.
    * Under  [Access Control > Authorization](https://console.developers.google.com/project/_/sql/instances/polls/access-control/users), Click
          "Create user account". Create a username and password and edit mysite/settings.py DATABASES
          to reflect this. Replace `<your-database-user>` and `<your-database-password>` with these variables.

Note in myproject/settings.py, the deployed app does not use the IP or user created, but instead talks to the instance through a Unix
socket as root. When testing locally, use the settings created above to access the database.

1. Create and run the Django migrations:

    ```
    python manage.py migrate
    ```


1. Run this project locally from the command line:

   ```
   dev_appserver.py app.yaml
   ```

  You can also run the server using Django's server, assuming you install the dependencies:
  ```
  pip install MySQLdb
  python manage.py runserver
  ```

Visit the application [http://localhost:8080](http://localhost:8080)

See [the development server documentation](https://developers.google.com/appengine/docs/python/tools/devserver)
for options when running dev_appserver.

## Deploy
To deploy the application:

1. Use the [Google Developer's Console](https://console.developer.google.com) to create a
   project, and note the project ID created. The project ID is sometimes the project
   name provided, and sometimes an auto-generated name.
1. Collect the static files into the static/ directory
   ```
   python manage.py collectstatic
   ```
1. Verify that `<your-cloud-project-id>` and `<your-database-name>` have been replaced in mysite/settings.py
   with your Cloud Project ID and your database name respectively.
1. [Deploy the
   application](https://developers.google.com/appengine/docs/python/tools/uploadinganapp) with

   ```
   appcfg.py -A <your-project-id> update app.yaml
   ```

   or using the new [gcloud SDK](https://cloud.google.com/sdk/?hl=en) commands.
   ```
   gcloud init # only required once
   gcloud preview app deploy app.yaml --promote
   ```

1. Congratulations!  Your application is now live at https://your-app-id.appspot.com

### Installing Libraries
See the [Third party
libraries](https://developers.google.com/appengine/docs/python/tools/libraries27)
page for libraries that are already included in the SDK.  To include SDK
libraries, add them in your app.yaml file. Other than libraries included in
the SDK, only pure python libraries may be added to an App Engine project.

Alternatively, pure Python libraries can be added to requirements.txt, and
installed using `pip -t` into the lib/ folder and accessed directly through
there.

### Feedback
Star this repo if you found it useful. Use the github issue tracker to give
feedback on this repo.

## Contributing changes
See [CONTRIBUTING.md](CONTRIBUTING.md)

## Licensing
See [LICENSE](LICENSE)
